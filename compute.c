//
// swaption.cpp
//
// Authors      : Mark Broadie, Jatin Dewanwala
// Collaborator : Mikhail Smelyanskiy, Intel, Jike Chong (Berkeley)
//
// Routines to compute various security prices using HJM framework (via Simulation).
//
#include <math.h>
#include <string.h>
#include "compute.h"

#define TRIALS 1000000
#define BLOCKSIZE 16
#define YEARS 5.5

// Length of time steps
#define DELTA (YEARS/N)
#define SQRT_DELTA 0.7071067811865476


//
// Returns the inverse of cumulative normal distribution function.
//
// Reference: Moro, B., 1995, "The Full Monte," RISK (February), 57-58.
//
static double cum_normal_inv(double u) {
  const double x = u - 0.5;

  if (fabs(x) < 0.42) {
    // 얘만 수행하는 병렬화를 해야됨
    double r = x * x;
    return x * (((-25.44106049637*r + 41.39119773534)*r - 18.61500062529)*r + 2.50662823884)
      / ((((3.13082909833*r - 21.06224101826)*r + 23.08336743743)*r - 8.47351093090)*r + 1.0);
  } else {
    // 조건 밖에 해당되어서 특별처리하는부분
    // 이거 근사해서 빠르게 할 수 있을지도
    double r = x > 0.0 ? 1.0 - u : u;
    r = log(-log(r)); // 느림!!
    r = 0.3374754822726147 + r * (0.9761690190917186 + r * (0.1607979714918209 + r *
       (0.0276438810333863 + r * (0.0038405729373609 + r * (0.0003951896511919 + r *
       (0.0000321767881768 + r * (0.0000002888167364 + r *  0.0000003960315187 )))))));
    return x >= 0.0 ? r : -r;
  }
}


//
// Uniform random number generator
//
// 이 함수는 reentrant 합니다.
//
static double uniform_random(long ix) {
  ix *= 1513517L;
  ix %= 2147483647L;
  long k1 = ix/127773L;
  ix = 16807L*(ix - k1*127773L) - k1*2836L;
  if (ix < 0) { ix += 2147483647L; }
  return ix * 4.656612875e-10;
}


//
// This function computes and stores an HJM Path for given inputs
//
// 대부분
//
static void hjm_path(
    // Matrix that stores generated HJM path (Output)
    double ppdHJMPath[restrict N][N*BLOCKSIZE],
    // t=0 Forward curve
    const double pdForward[restrict],
    // Vector containing total drift corrections for different maturities
    const double pdTotalDrift[restrict],
    // Factor volatilities
    const double ppdFactors[restrict FACTORS][N - 1],
    // Random number seed
    long seed)
{
  // t=0 forward curve stored N first row of ppdHJMPath
  // At time step 0: insert expected drift
  // rest reset to 0
  // KCM: if you are not going to do parallelization,change the order of the
  // loop. {for (j) for(b)} {for(i) memset(ppdHJMPATH[i])}
  for (int j = 0; j < N; ++j) {
    double val = pdForward[j];
    for (int b = 0; b < BLOCKSIZE; ++b) {
      ppdHJMPath[0][BLOCKSIZE*j + b] = val;
    }
  }

  // Initializing HJMPath to zero
  for (int i = 1; i < N; ++i) {
    memset(ppdHJMPath[i], 0, sizeof ppdHJMPath[i]);
  }


  //
  // Sequentially generating random numbers
  //
  double pdZ[FACTORS][N*BLOCKSIZE];
  for(int b = 0; b < BLOCKSIZE; ++b) {
    for (int j = 1; j < N; ++j) {
      for (int l = 0; l < FACTORS; ++l) {
        //compute random number in exact same sequence
        pdZ[l][BLOCKSIZE*j + b] = uniform_random(seed++);  /* 10% of the total executition time */
      }
    }
  }


  //
  // shocks to hit various factors for forward curve at t
  // 18% of the total executition time
  //
  for (int l = 0; l < FACTORS; ++l) {
    for (int b = 0; b < BLOCKSIZE; ++b) {
      for (int j = 1; j < N; ++j) {
        // 18% of the total executition time
        pdZ[l][BLOCKSIZE*j + b] = cum_normal_inv(pdZ[l][BLOCKSIZE*j + b]);
      }
    }
  }


  //
  // Generation of HJM Path1
  //

  // b is the blocks
  for(int b = 0; b < BLOCKSIZE; ++b){
    // j is the timestep
    for (int j = 1; j < N; ++j) {
      // l is the future steps
      for (int l = 0; l < N - j; ++l){
        // Total shock by which the forward curve is hit at (t, T-t)
        double dTotalShock = 0;

        // i steps through the stochastic factors
        for (int i = 0; i < FACTORS; ++i){
          dTotalShock += ppdFactors[i][l] * pdZ[i][BLOCKSIZE*j + b];
        }

        // As per formula
        ppdHJMPath[j][BLOCKSIZE*l+b] = ppdHJMPath[j-1][BLOCKSIZE*(l+1)+b] + pdTotalDrift[l]*DELTA + SQRT_DELTA*dTotalShock;
      }
    }
  }
}


//
// swaption.c
//
static void discount_factors(
    double pdDiscountFactors[restrict],
    int num,
    double years,
    const double pdRatePath[restrict])
{
  // HJM time-step length
  const double delta = years/num;

  // Precompute the exponientials
  double pdexpRes[(num - 1)*BLOCKSIZE];
  for (int j = 0; j < (num - 1)*BLOCKSIZE; ++j) { pdexpRes[j] = -pdRatePath[j]*delta; }
  for (int j = 0; j < (num - 1)*BLOCKSIZE; ++j) { pdexpRes[j] = exp(pdexpRes[j]);  }


  // Initializing the discount factor vector
  for (int i = 0; i < num*BLOCKSIZE; ++i) {
    pdDiscountFactors[i] = 1.0;
  }

  for (int i = 1; i < num; ++i) {
    for (int b = 0; b < BLOCKSIZE; ++b) {
      for (int j = 0; j < i; ++j) {
        // kcm: do both loop unrolling and reorder pdexpRes vector elements above. -> SSE
        // optimization is possible.
        pdDiscountFactors[i*BLOCKSIZE + b] *= pdexpRes[j*BLOCKSIZE + b];
      }
    }
  }
}


void swaption(
    // result vector that will store simulation results in the form:
    //     Swaption Price
    //     Swaption Standard Error
    double * __restrict__ result,

    // HJM Framework Parameters
    double dStrikeCont,
    const double * __restrict__ pdYield,
    const double ppdFactors[FACTORS][N - 1])
{
  //
  // Mathmatical constants
  //
  const double dPaymentInterval = 1.0;
  const int iFreqRatio = dPaymentInterval/DELTA + 0.5;
  const double dMaturity = 1.0;
  const int iSwapVectorLength = N - dMaturity/DELTA + 0.5;
  const int iSwapStartTimeIndex = dMaturity/DELTA + 0.5;
  const double dTenor = 2.0;
  const int iSwapTimePoints = dTenor/DELTA + 0.5;
  const double dSwapVectorYears = iSwapVectorLength*DELTA;


  // Store swap payoffs
  double pdSwapPayoffs[iSwapVectorLength];
  memset(pdSwapPayoffs, 0, sizeof pdSwapPayoffs);
  for (int i = iFreqRatio; i <= iSwapTimePoints; i += iFreqRatio) {
    double tmp = exp(dStrikeCont*dPaymentInterval);
    // Normally, the bond pays coupon equal to this amount
    // But at terminal time point, bond pays coupon plus par amount
    pdSwapPayoffs[i] = i == iSwapTimePoints ? tmp : tmp - 1;
  }
  // Generating forward curve at t=0 from supplied yield curve
  double pdForward[N];
  pdForward[0] = pdYield[0];
  for (int i = 1; i < N; ++i) {
    pdForward[i] = (i + 1)*pdYield[i] - i*pdYield[i - 1];
  }


  //
  // Computation of drifts from factor volatilities
  //
  double ppdDrifts[FACTORS][N - 1];
  double pdTotalDrift[N- 1];
  // Computation of factor drifts for shortest maturity
  for (int i = 0; i < FACTORS; ++i) {
    ppdDrifts[i][0] = 0.5*DELTA*ppdFactors[i][0]*ppdFactors[i][0];
  }
  // Computation of factor drifts for other maturities
  for (int i = 0; i < FACTORS; ++i) {
    for (int j = 1; j < N - 1; ++j) {
      double sum0 = 0;
      for(int l = 0; l < j; ++l) { sum0 -= ppdDrifts[i][l]; }
      ppdDrifts[i][j] = sum0;

      double sum = 0;
      for(int l = 0; l <= j; ++l) { sum += ppdFactors[i][l]; }
      ppdDrifts[i][j] += 0.5*DELTA*sum*sum;
    }
  }
  // Computation of total drifts for all maturities
  for (int i = 0; i < N - 1; ++i) {
    double sum = 0;
    for(int j = 0; j < FACTORS; ++j) { sum += ppdDrifts[j][i]; }
    pdTotalDrift[i] = sum;
  }


  //
  // Simulations
  //
  double dSumSimSwaptionPrice = 0;
  double dSumSquareSimSwaptionPrice = 0;
  long iRndSeed = 100;

  for (int l = 0; l< TRIALS; l += BLOCKSIZE) {
    // For each trial a new HJM Path is generated
    double ppdHJMPath[N][N*BLOCKSIZE];
    hjm_path(ppdHJMPath, pdForward, pdTotalDrift, ppdFactors, iRndSeed); // 51% of the time goes here
    iRndSeed += BLOCKSIZE*(N - 1)*FACTORS;

    // Now we compute the discount factor vector
    // 여긴 안해도 될거같음
    double pdDiscountingRatePath[N*BLOCKSIZE];
    for (int i = 0; i < N; ++i) {
      for (int b = 0; b < BLOCKSIZE; ++b) {
        pdDiscountingRatePath[BLOCKSIZE*i + b] = ppdHJMPath[i][0 + b];
      }
    }

    // Store discount factors for the rate path along which the swaption
    double pdPayoffDiscountFactors[N*BLOCKSIZE];
    discount_factors(pdPayoffDiscountFactors, N, YEARS, pdDiscountingRatePath); // 15% of the time goes here

    // Now we compute discount factors along the swap path
    double pdSwapRatePath[iSwapVectorLength*BLOCKSIZE];
    for (int i = 0; i < iSwapVectorLength; ++i) {
      for (int b = 0; b < BLOCKSIZE; ++b) {
        pdSwapRatePath[i*BLOCKSIZE + b] = ppdHJMPath[iSwapStartTimeIndex][i*BLOCKSIZE + b];
      }
    }

    // Payments made will be discounted corresponding to swaption maturity
    double pdSwapDiscountFactors[iSwapVectorLength*BLOCKSIZE];
    discount_factors(pdSwapDiscountFactors, iSwapVectorLength, dSwapVectorYears, pdSwapRatePath);


    //
    // Simulation
    //
    for (int b = 0; b < BLOCKSIZE; ++b) {
      double sum = -1;
      for (int i = 0; i < iSwapVectorLength; ++i) {
        sum += pdSwapPayoffs[i]*pdSwapDiscountFactors[i*BLOCKSIZE + b];
      }

      double result = sum > 0 ? sum*pdPayoffDiscountFactors[iSwapStartTimeIndex*BLOCKSIZE + b] : 0;

      // Accumulate
      dSumSimSwaptionPrice += result;
      dSumSquareSimSwaptionPrice += result*result;
    }
  }

  // Store results
  result[0] = dSumSimSwaptionPrice/TRIALS;
  result[1] = sqrt((dSumSquareSimSwaptionPrice - dSumSimSwaptionPrice*dSumSimSwaptionPrice/TRIALS)/(TRIALS - 1.0)/TRIALS);
}
