//
// swaption.cpp
//
// Authors      : Mark Broadie, Jatin Dewanwala
// Collaborator : Mikhail Smelyanskiy, Intel, Jike Chong (Berkeley)
//
// Routines to compute various security prices using HJM framework (via Simulation).
//
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "compute.h"


//
// Returns the inverse of cumulative normal distribution function.
//
// Reference: Moro, B., 1995, "The Full Monte," RISK (February), 57-58.
//
static double cum_normal_inv(double u) {
  const double a[4] = { 2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637 };
  const double b[4] = { -8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833 };
  const double c[9] = {
    0.3374754822726147, 0.9761690190917186, 0.1607979714918209,
    0.0276438810333863, 0.0038405729373609, 0.0003951896511919,
    0.0000321767881768, 0.0000002888167364, 0.0000003960315187
  };

  const double x = u - 0.5;
  double r;
  if (fabs (x) < 0.42) {
    // 얘만 수행하는 병렬화를 해야됨
    r = x * x;
    r = x * ((( a[3]*r + a[2]) * r + a[1]) * r + a[0])/
          ((((b[3] * r+ b[2]) * r + b[1]) * r + b[0]) * r + 1.0);
    return r;
  }

  // 조건 밖에 해당되어서 특별처리하는부분
  // 이거 근사하기
  r = u;
  if (x > 0.0) { r = 1.0 - u; }
  r = log(-log(r)); //!!!!!!!!
  r = c[0] + r * (c[1] + r *
       (c[2] + r * (c[3] + r *
       (c[4] + r * (c[5] + r * (c[6] + r * (c[7] + r*c[8])))))));
  if (x < 0.0) { r = -r; }

  return r;
}


//
// Uniform random number generator
// 병렬화 가능함. s는 계속 1씩 증가할 뿐. 나머지 코드는 그대로 병렬화 가능.
// 그러니까 vector에 [시작값, 시작값+1, 시작값+2, ... ]으로 채워놓고 밑의 연산 적용하면 됨.
// 대놓고 병렬화하라고 준 랜덤이네.
//
static double uniform_random(long *s) {
  long ix = *s;
  *s = ix+1;
  ix *= 1513517L;
  ix %= 2147483647L;
  long k1 = ix/127773L;
  ix = 16807L*(ix - k1*127773L) - k1*2836L;
  if (ix < 0) { ix = ix + 2147483647L; }

  return ix * 4.656612875e-10;
}


//
// This function computes and stores an HJM Path for given inputs
//
// 대부분
//
static int hjm_path(
    double ppdHJMPath[restrict N][N*BLOCKSIZE], // Matrix that stores generated HJM path (Output)
    double dYears, // Number of years
    double pdForward[restrict], // t=0 Forward curve
    double pdTotalDrift[restrict], // Vector containing total drift corrections for different maturities
    double ppdFactors[FACTORS][N - 1], // Factor volatilities
    long * restrict lRndSeed) // Random number seed
{
  int i,j,l; //looping variables
  double dTotalShock; //total shock by which the forward curve is hit at (t, T-t)
  double ddelt, sqrt_ddelt; //length of time steps

  ddelt = (double)(dYears/N);
  sqrt_ddelt = sqrt(ddelt);

  double pdZ[FACTORS][N*BLOCKSIZE]; // vector to store random normals
  double randZ[FACTORS][N*BLOCKSIZE]; // vector to store random normals


  // t=0 forward curve stored N first row of ppdHJMPath
  // At time step 0: insert expected drift
  // rest reset to 0
  // KCM: if you are not going to do parallelization,change the order of the
  // loop. {for (j) for(b)} {for(i) memset(ppdHJMPATH[i])}
  for (int b = 0; b < BLOCKSIZE; b++) {
    for (j = 0; j <= N - 1; j++) {
      ppdHJMPath[0][BLOCKSIZE*j + b] = pdForward[j];

      // Initializing HJMPath to zero
      for (i = 1; i <= N - 1; ++i) {
        ppdHJMPath[i][BLOCKSIZE*j + b] = 0;
      }
    }
  }


  //
  // Sequentially generating random numbers
  //
  for(int b=0; b<BLOCKSIZE; b++){
    for(int s=0; s<1; s++){
      for (j=1;j<=N-1;++j){
        for (l=0;l<=FACTORS-1;++l){
          //compute random number in exact same sequence
          // 병렬화가 어렵다.
          randZ[l][BLOCKSIZE*j + b + s] = uniform_random(lRndSeed);  /* 10% of the total executition time */
        }
      }
    }
  }


  // 할수있어! 병렬화 below:


  //
  // shocks to hit various factors for forward curve at t
  // 18% of the total executition time
  //
  for (int l = 0; l <= FACTORS - 1; ++l) {
    for (int b = 0; b < BLOCKSIZE; b++) {
      for (int j = 1; j <= N - 1; ++j) {
        // 18% of the total executition time
        pdZ[l][BLOCKSIZE*j + b] = cum_normal_inv(randZ[l][BLOCKSIZE*j + b]);
      }
    }
  }


  //
  // Generation of HJM Path1
  //
  for(int b=0; b<BLOCKSIZE; b++){ // b is the blocks
    for (j=1;j<=N-1;++j) {// j is the timestep

      for (l=0;l<=N-(j+1);++l){ // l is the future steps
        dTotalShock = 0;

        for (i=0;i<=FACTORS-1;++i){// i steps through the stochastic factors
          dTotalShock += ppdFactors[i][l]* pdZ[i][BLOCKSIZE*j + b];
        }

        ppdHJMPath[j][BLOCKSIZE*l+b] = ppdHJMPath[j-1][BLOCKSIZE*(l+1)+b]+ pdTotalDrift[l]*ddelt + sqrt_ddelt*dTotalShock;
        //as per formula
      }
    }
  } // end Blocks

  return 1;
}


//
// swaption.c
//
static inline int Discount_Factors_Blocking(
    double pdDiscountFactors[restrict],
    int num,
    double dYears,
    double pdRatePath[restrict])
{
  int i,j,b; // Looping variables

  double ddelt;			//HJM time-step length
  ddelt = (double) (dYears/num);

  double pdexpRes[(num - 1)*BLOCKSIZE];
  //precompute the exponientials
  for (j=0; j<=(num-1)*BLOCKSIZE-1; ++j){ pdexpRes[j] = -pdRatePath[j]*ddelt; }
  for (j=0; j<=(num-1)*BLOCKSIZE-1; ++j){ pdexpRes[j] = exp(pdexpRes[j]);  }


  //initializing the discount factor vector
  for (i=0; i<(num)*BLOCKSIZE; ++i)
    pdDiscountFactors[i] = 1.0;

  for (i=1; i<=num-1; ++i){
    for (b=0; b<BLOCKSIZE; b++){
      for (j=0; j<=i-1; ++j){
        // kcm: do both loop unrolling and reorder pdexpRes vector elements above. -> SSE
        // optimization is possible.
        pdDiscountFactors[i*BLOCKSIZE + b] *= pdexpRes[j*BLOCKSIZE + b];
      }
    }
  }

  return 1;
}



static inline int HJM_Yield_to_Forward(
    double pdForward[restrict], // Forward curve to be outputted
    double pdYield[restrict]) // Input yield curve
{
  //This function computes forward rates from supplied yield rates.

  int iSuccess=0;
  int i;

  //forward curve computation
  pdForward[0] = pdYield[0];
  for(i=1;i<=N-1; ++i){
    pdForward[i] = (i+1)*pdYield[i] - i*pdYield[i-1];	//as per formula
    //printf("pdForward: %f = (%d+1)*%f - %d*%f \n", pdForward[i], i, pdYield[i], i, pdYield[i-1]);
  }
  iSuccess=1;
  return iSuccess;
}


static inline int HJM_Drifts(
    double pdTotalDrift[restrict N-1], // Output vector that stores the total drift correction for each maturity
    double ppdDrifts[restrict FACTORS][N - 1], // Output matrix that stores drift correction for each factor for each maturity
    double dYears,
    double ppdFactors[restrict FACTORS][N - 1]) // Input factor volatilities
{
  //This function computes drift corrections required for each factor for each maturity based on given factor volatilities

  int iSuccess =0;
  int i, j, l; //looping variables
  double ddelt = (double) (dYears/N);
  double dSumVol;

  //computation of factor drifts for shortest maturity
  for (i=0; i<=FACTORS-1; ++i)
    ppdDrifts[i][0] = 0.5*ddelt*(ppdFactors[i][0])*(ppdFactors[i][0]);

  //computation of factor drifts for other maturities
  for (i=0; i<=FACTORS-1;++i)
    for (j=1; j<=N-2; ++j)
    {
      ppdDrifts[i][j] = 0;
      for(l=0;l<=j-1;++l)
        ppdDrifts[i][j] -= ppdDrifts[i][l];
      dSumVol=0;
      for(l=0;l<=j;++l)
        dSumVol += ppdFactors[i][l];
      ppdDrifts[i][j] += 0.5*ddelt*(dSumVol)*(dSumVol);
    }

  //computation of total drifts for all maturities
  for(i=0;i<=N-2;++i)
  {
    pdTotalDrift[i]=0;
    for(j=0;j<=FACTORS-1;++j)
      pdTotalDrift[i]+= ppdDrifts[j][i];
  }

  iSuccess=1;
  return iSuccess;
}



int swaption(
    // result vector that will store simulation results in the form:
    //     Swaption Price
    //     Swaption Standard Error
    double * __restrict__ result,

    double dStrike,
    // HJM Framework Parameters (please refer HJM.cpp for explanation of variables and functions)
    double * __restrict__ pdYield,
    double ppdFactors[FACTORS][N - 1])
{
  //
  // Constants
  //
  const double dCompounding = 0; // Compounding convention used for quoting the strike (0 => continuous, 0.5 => semi-annual, 1 => annual)
  const double dMaturity = 1; // Maturity of the swaption (time to expiration)
  const double dTenor = 2.0; // Tenor of the swap
  const double dPaymentInterval = 1.0; //frequency of swap payments e.g. dPaymentInterval = 0.5 implies a swap payment every half year
  const double dYears = 5.5;
  const long lTrials = 1000000;


  int iSuccess = 0;
  long iRndSeed = 100;
  int i;
  int b; //block looping variable
  long l; //looping variables

  double ddelt = (double)(dYears/N);				//ddelt = HJM matrix time-step width. e.g. if dYears = 5yrs and
  //N = no. of time points = 10, then ddelt = step length = 0.5yrs
  int iFreqRatio = (int)(dPaymentInterval/ddelt + 0.5);		// = ratio of time gap between swap payments and HJM step-width.
  //e.g. dPaymentInterval = 1 year. ddelt = 0.5year. This implies that a swap
  //payment will be made after every 2 HJM time steps.

  double dStrikeCont;				//Strike quoted in continuous compounding convention.
  //As HJM rates are continuous, the K in max(R-K,0) will be dStrikeCont and not dStrike.
  if(dCompounding==0) {
    dStrikeCont = dStrike;		//by convention, dCompounding = 0 means that the strike entered by user has been quoted
    //using continuous compounding convention
  } else {
    //converting quoted strike to continuously compounded strike
    dStrikeCont = (1/dCompounding)*log(1+dStrike*dCompounding);
  }
  //e.g., let k be strike quoted in semi-annual convention. Therefore, 1$ at the end of
  //half a year would earn = (1+k/2). For converting to continuous compounding,
  //(1+0.5*k) = exp(K*0.5)
  // => K = (1/0.5)*ln(1+0.5*k)

  //
  // HJM Framework vectors and matrices
  //


  // *******************************
  double ppdHJMPath[N][N*BLOCKSIZE];
  double pdForward[N];
  double ppdDrifts[FACTORS][N - 1];
  double pdTotalDrift[N-1];

  // Length of the HJM rate path at the time index corresponding to swaption maturity.
  // This is the length of the HJM rate path at the time index
  int iSwapVectorLength = N - dMaturity/ddelt + 0.5;

  //==================================
  // Per Trial data
  double pdDiscountingRatePath[N*BLOCKSIZE];	  //vector to store rate path along which the swaption payoff will be discounted
  double pdPayoffDiscountFactors[N*BLOCKSIZE];  //vector to store discount factors for the rate path along which the swaption

  // Payoff will be discounted
  // Vector to store the rate path along which the swap payments made will be discounted
  double pdSwapRatePath[iSwapVectorLength*BLOCKSIZE];
  // Vector to store discount factors for the rate path along which the swap
  double pdSwapDiscountFactors[iSwapVectorLength*BLOCKSIZE];

  //payments made will be discounted
  // corresponding to swaption maturity.
  double pdSwapPayoffs[iSwapVectorLength]; //vector to store swap payoffs


  int iSwapStartTimeIndex;
  int iSwapTimePoints;
  double dSwapVectorYears;

  double dSwaptionPayoff;
  double dDiscSwaptionPayoff;
  double dFixedLegValue;

  // Accumulators
  double dSumSimSwaptionPrice;
  double dSumSquareSimSwaptionPrice;

  // Final returned results
  double dSimSwaptionMeanPrice;
  double dSimSwaptionStdError;
  // *******************************


  iSwapStartTimeIndex = (int) (dMaturity/ddelt + 0.5);	//Swap starts at swaption maturity
  iSwapTimePoints = (int) (dTenor/ddelt + 0.5);			//Total HJM time points corresponding to the swap's tenor
  dSwapVectorYears = (double) (iSwapVectorLength*ddelt);



  //now we store the swap payoffs in the swap payoff vector
  for (i=0;i<=iSwapVectorLength-1;++i)
    pdSwapPayoffs[i] = 0.0; //initializing to zero
  for (i=iFreqRatio;i<=iSwapTimePoints;i+=iFreqRatio)
  {
    if(i != iSwapTimePoints)
      pdSwapPayoffs[i] = exp(dStrikeCont*dPaymentInterval) - 1; //the bond pays coupon equal to this amount
    if(i == iSwapTimePoints)
      pdSwapPayoffs[i] = exp(dStrikeCont*dPaymentInterval); //at terminal time point, bond pays coupon plus par amount
  }

  //generating forward curve at t=0 from supplied yield curve
  iSuccess = HJM_Yield_to_Forward(pdForward, pdYield);
  if (iSuccess!=1)
    return iSuccess;

  //computation of drifts from factor volatilities
  iSuccess = HJM_Drifts(pdTotalDrift, ppdDrifts, dYears, ppdFactors);
  if (iSuccess!=1)
    return iSuccess;

  dSumSimSwaptionPrice = 0.0;
  dSumSquareSimSwaptionPrice = 0.0;

  //Simulations begin:
  for (l=0;l<=lTrials-1;l+=BLOCKSIZE) {
    //For each trial a new HJM Path is generated
    iSuccess = hjm_path(ppdHJMPath, dYears, pdForward, pdTotalDrift,ppdFactors, &iRndSeed); /* GC: 51% of the time goes here */
    if (iSuccess!=1)
      return iSuccess;

    //now we compute the discount factor vector

    // 여긴 안해도 될거같음
    for(i=0;i<=N-1;++i){
      for(b=0;b<=BLOCKSIZE-1;b++){
        pdDiscountingRatePath[BLOCKSIZE*i + b] = ppdHJMPath[i][0 + b];
      }
    }
    iSuccess = Discount_Factors_Blocking(pdPayoffDiscountFactors, N, dYears, pdDiscountingRatePath); /* 15% of the time goes here */

    if (iSuccess!=1)
      return iSuccess;

    //now we compute discount factors along the swap path
    for (i=0;i<=iSwapVectorLength-1;++i){
      for(b=0;b<BLOCKSIZE;b++){
        pdSwapRatePath[i*BLOCKSIZE + b] =
          ppdHJMPath[iSwapStartTimeIndex][i*BLOCKSIZE + b];
      }
    }
    iSuccess = Discount_Factors_Blocking(pdSwapDiscountFactors, iSwapVectorLength, dSwapVectorYears, pdSwapRatePath);
    if (iSuccess!=1)
      return iSuccess;


    // ========================
    // Simulation
    for (b=0;b<BLOCKSIZE;b++){
      dFixedLegValue = 0.0;
      for (i=0;i<=iSwapVectorLength-1;++i){
        dFixedLegValue += pdSwapPayoffs[i]*pdSwapDiscountFactors[i*BLOCKSIZE + b];
      }

      double tmp = dFixedLegValue - 1.0;
      dSwaptionPayoff = tmp > 0 ? tmp : 0;

      dDiscSwaptionPayoff = dSwaptionPayoff*pdPayoffDiscountFactors[iSwapStartTimeIndex*BLOCKSIZE + b];

      // ========= end simulation ======================================

      // accumulate into the aggregating variables =====================
      dSumSimSwaptionPrice += dDiscSwaptionPayoff;
      dSumSquareSimSwaptionPrice += dDiscSwaptionPayoff*dDiscSwaptionPayoff;
    } // END BLOCK simulation
  }

  // Simulation Results Stored
  dSimSwaptionMeanPrice = dSumSimSwaptionPrice/lTrials;
  dSimSwaptionStdError = sqrt((dSumSquareSimSwaptionPrice-dSumSimSwaptionPrice*dSumSimSwaptionPrice/lTrials)/
      (lTrials-1.0))/sqrt((double)lTrials);

  // Store results
  result[0] = dSimSwaptionMeanPrice;
  result[1] = dSimSwaptionStdError;
  return 1;
}
