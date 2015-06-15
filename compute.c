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
#include "helper.h"
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

  double x = u - 0.5;
  double r;
  if (fabs (x) < 0.42) {
    r = x * x;
    r = x * ((( a[3]*r + a[2]) * r + a[1]) * r + a[0])/
          ((((b[3] * r+ b[2]) * r + b[1]) * r + b[0]) * r + 1.0);
    return r;
  }

  r = u;
  if (x > 0.0) { r = 1.0 - u; }
  r = log(-log(r));
  r = c[0] + r * (c[1] + r *
       (c[2] + r * (c[3] + r *
       (c[4] + r * (c[5] + r * (c[6] + r * (c[7] + r*c[8])))))));
  if (x < 0.0) { r = -r; }

  return r;
}


//
// Uniform random number generator
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


static void serial_b(double **pdZ, double **randZ, int BLOCKSIZE, int iN, int iFactors) {
  for(int l = 0; l <= iFactors - 1; ++l){
    for(int b = 0; b < BLOCKSIZE; b++){
      for (int j = 1; j <= iN - 1; ++j){
        // 18% of the total executition time
        pdZ[l][BLOCKSIZE*j + b] = cum_normal_inv(randZ[l][BLOCKSIZE*j + b]);
      }
    }
  }
}


//
// This function computes and stores an HJM Path for given inputs
//
static int hjm_path(
    double **ppdHJMPath, // Matrix that stores generated HJM path (Output)
    int iN, // Number of time-steps
    int iFactors, // Number of factors in the HJM framework
    double dYears, // Number of years
    double *pdForward, // t=0 Forward curve
    double *pdTotalDrift, // Vector containing total drift corrections for different maturities
    double **ppdFactors, // Factor volatilities
    long *lRndSeed, // Random number seed
    int BLOCKSIZE)
{
  int iSuccess = 0;
  int i,j,l; //looping variables
  double **pdZ; //vector to store random normals
  double **randZ; //vector to store random normals
  double dTotalShock; //total shock by which the forward curve is hit at (t, T-t)
  double ddelt, sqrt_ddelt; //length of time steps

  ddelt = (double)(dYears/iN);
  sqrt_ddelt = sqrt(ddelt);

  pdZ   = dmatrix(iFactors-1, iN*BLOCKSIZE -1); //assigning memory
  randZ = dmatrix(iFactors-1, iN*BLOCKSIZE -1); //assigning memory


  // t=0 forward curve stored iN first row of ppdHJMPath
  // At time step 0: insert expected drift
  // rest reset to 0
  for (int b = 0; b < BLOCKSIZE; b++) {
    for (j = 0; j <= iN - 1; j++) {
      ppdHJMPath[0][BLOCKSIZE*j + b] = pdForward[j];

      // Initializing HJMPath to zero
      for (i = 1; i <= iN - 1; ++i) {
        ppdHJMPath[i][BLOCKSIZE*j + b] = 0;
      }
    }
  }


  //
  // Sequentially generating random numbers
  //
  for(int b=0; b<BLOCKSIZE; b++){
    for(int s=0; s<1; s++){
      for (j=1;j<=iN-1;++j){
        for (l=0;l<=iFactors-1;++l){
          //compute random number in exact same sequence
          randZ[l][BLOCKSIZE*j + b + s] = uniform_random(lRndSeed);  /* 10% of the total executition time */
        }
      }
    }
  }


  //
  // shocks to hit various factors for forward curve at t
  // 18% of the total executition time
  //
  serial_b(pdZ, randZ, BLOCKSIZE, iN, iFactors);


  //
  // Generation of HJM Path1
  //
  for(int b=0; b<BLOCKSIZE; b++){ // b is the blocks
    for (j=1;j<=iN-1;++j) {// j is the timestep

      for (l=0;l<=iN-(j+1);++l){ // l is the future steps
        dTotalShock = 0;

        for (i=0;i<=iFactors-1;++i){// i steps through the stochastic factors
          dTotalShock += ppdFactors[i][l]* pdZ[i][BLOCKSIZE*j + b];
        }

        ppdHJMPath[j][BLOCKSIZE*l+b] = ppdHJMPath[j-1][BLOCKSIZE*(l+1)+b]+ pdTotalDrift[l]*ddelt + sqrt_ddelt*dTotalShock;
        //as per formula
      }
    }
  } // end Blocks
  // -----------------------------------------------------

  free_dmatrix(pdZ);
  free_dmatrix(randZ);
  iSuccess = 1;
  return iSuccess;
}


//
// swaption.c
//
static inline int Discount_Factors_Blocking(double *pdDiscountFactors, int iN, double dYears, double *pdRatePath, int BLOCKSIZE) {
  int i,j,b;				//looping variables
  int iSuccess;			//return variable

  double ddelt;			//HJM time-step length
  ddelt = (double) (dYears/iN);

  double *pdexpRes;
  pdexpRes = dvector((iN-1)*BLOCKSIZE-1);
  //precompute the exponientials
  for (j=0; j<=(iN-1)*BLOCKSIZE-1; ++j){ pdexpRes[j] = -pdRatePath[j]*ddelt; }
  for (j=0; j<=(iN-1)*BLOCKSIZE-1; ++j){ pdexpRes[j] = exp(pdexpRes[j]);  }


  //initializing the discount factor vector
  for (i=0; i<(iN)*BLOCKSIZE; ++i)
    pdDiscountFactors[i] = 1.0;

  for (i=1; i<=iN-1; ++i){
    //printf("\nVisiting timestep %d : ",i);
    for (b=0; b<BLOCKSIZE; b++){
      //printf("\n");
      for (j=0; j<=i-1; ++j){
        pdDiscountFactors[i*BLOCKSIZE + b] *= pdexpRes[j*BLOCKSIZE + b];
        //printf("(%f) ",pdexpRes[j*BLOCKSIZE + b]);
      }
    } // end Block loop
  }

  free_dvector(pdexpRes);
  iSuccess = 1;
  return iSuccess;
}



static inline int HJM_Yield_to_Forward (double *pdForward,	//Forward curve to be outputted
    int iN,				//Number of time-steps
    double *pdYield)		//Input yield curve
{
  //This function computes forward rates from supplied yield rates.

  int iSuccess=0;
  int i;

  //forward curve computation
  pdForward[0] = pdYield[0];
  for(i=1;i<=iN-1; ++i){
    pdForward[i] = (i+1)*pdYield[i] - i*pdYield[i-1];	//as per formula
    //printf("pdForward: %f = (%d+1)*%f - %d*%f \n", pdForward[i], i, pdYield[i], i, pdYield[i-1]);
  }
  iSuccess=1;
  return iSuccess;
}


static inline double dMax( double dA, double dB ) { return (dA>dB ? dA:dB); }


static inline int HJM_Drifts(double *pdTotalDrift,	//Output vector that stores the total drift correction for each maturity
    double **ppdDrifts,		//Output matrix that stores drift correction for each factor for each maturity
    int iN,
    int iFactors,
    double dYears,
    double **ppdFactors)		//Input factor volatilities
{
  //This function computes drift corrections required for each factor for each maturity based on given factor volatilities

  int iSuccess =0;
  int i, j, l; //looping variables
  double ddelt = (double) (dYears/iN);
  double dSumVol;

  //computation of factor drifts for shortest maturity
  for (i=0; i<=iFactors-1; ++i)
    ppdDrifts[i][0] = 0.5*ddelt*(ppdFactors[i][0])*(ppdFactors[i][0]);

  //computation of factor drifts for other maturities
  for (i=0; i<=iFactors-1;++i)
    for (j=1; j<=iN-2; ++j)
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
  for(i=0;i<=iN-2;++i)
  {
    pdTotalDrift[i]=0;
    for(j=0;j<=iFactors-1;++j)
      pdTotalDrift[i]+= ppdDrifts[j][i];
  }

  iSuccess=1;
  return iSuccess;
}



int swaption(double *pdSwaptionPrice, //Output vector that will store simulation results in the form:
    //Swaption Price
    //Swaption Standard Error
    //Swaption Parameters
    double dStrike,
    double dCompounding,     //Compounding convention used for quoting the strike (0 => continuous,
    //0.5 => semi-annual, 1 => annual).
    double dMaturity,	      //Maturity of the swaption (time to expiration)
    double dTenor,	      //Tenor of the swap
    double dPaymentInterval, //frequency of swap payments e.g. dPaymentInterval = 0.5 implies a swap payment every half
    //year
    //HJM Framework Parameters (please refer HJM.cpp for explanation of variables and functions)
    int iN,
    int iFactors,
    double dYears,
    double *pdYield,
    double **ppdFactors,
    //Simulation Parameters
    long iRndSeed,
    long lTrials,
    int BLOCKSIZE)

{
  int iSuccess = 0;
  int i;
  int b; //block looping variable
  long l; //looping variables

  double ddelt = (double)(dYears/iN);				//ddelt = HJM matrix time-step width. e.g. if dYears = 5yrs and
  //iN = no. of time points = 10, then ddelt = step length = 0.5yrs
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

  //HJM Framework vectors and matrices
  int iSwapVectorLength;  // Length of the HJM rate path at the time index corresponding to swaption maturity.

  double **ppdHJMPath;    // **** per Trial data **** //

  double *pdForward;
  double **ppdDrifts;
  double *pdTotalDrift;

  // *******************************
  ppdHJMPath = dmatrix(iN-1,iN*BLOCKSIZE-1);    // **** per Trial data **** //
  pdForward = dvector(iN-1);
  ppdDrifts = dmatrix(iFactors-1, iN-2);
  pdTotalDrift = dvector(iN-2);

  //==================================
  // **** per Trial data **** //
  double *pdDiscountingRatePath;	  //vector to store rate path along which the swaption payoff will be discounted
  double *pdPayoffDiscountFactors;  //vector to store discount factors for the rate path along which the swaption
  //payoff will be discounted
  double *pdSwapRatePath;			  //vector to store the rate path along which the swap payments made will be discounted
  double *pdSwapDiscountFactors;	  //vector to store discount factors for the rate path along which the swap
  //payments made will be discounted
  double *pdSwapPayoffs;			  //vector to store swap payoffs


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
  pdPayoffDiscountFactors = dvector(iN*BLOCKSIZE-1);
  pdDiscountingRatePath = dvector(iN*BLOCKSIZE-1);
  // *******************************

  iSwapVectorLength = (int) (iN - dMaturity/ddelt + 0.5);	//This is the length of the HJM rate path at the time index
  //corresponding to swaption maturity.
  // *******************************
  pdSwapRatePath = dvector(iSwapVectorLength*BLOCKSIZE - 1);
  pdSwapDiscountFactors  = dvector(iSwapVectorLength*BLOCKSIZE - 1);
  // *******************************
  pdSwapPayoffs = dvector(iSwapVectorLength - 1);


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
  iSuccess = HJM_Yield_to_Forward(pdForward, iN, pdYield);
  if (iSuccess!=1)
    return iSuccess;

  //computation of drifts from factor volatilities
  iSuccess = HJM_Drifts(pdTotalDrift, ppdDrifts, iN, iFactors, dYears, ppdFactors);
  if (iSuccess!=1)
    return iSuccess;

  dSumSimSwaptionPrice = 0.0;
  dSumSquareSimSwaptionPrice = 0.0;

  //Simulations begin:
  for (l=0;l<=lTrials-1;l+=BLOCKSIZE) {
    //For each trial a new HJM Path is generated
    iSuccess = hjm_path(ppdHJMPath, iN, iFactors, dYears, pdForward, pdTotalDrift,ppdFactors, &iRndSeed, BLOCKSIZE); /* GC: 51% of the time goes here */
    if (iSuccess!=1)
      return iSuccess;

    //now we compute the discount factor vector

    for(i=0;i<=iN-1;++i){
      for(b=0;b<=BLOCKSIZE-1;b++){
        pdDiscountingRatePath[BLOCKSIZE*i + b] = ppdHJMPath[i][0 + b];
      }
    }
    iSuccess = Discount_Factors_Blocking(pdPayoffDiscountFactors, iN, dYears, pdDiscountingRatePath, BLOCKSIZE); /* 15% of the time goes here */

    if (iSuccess!=1)
      return iSuccess;

    //now we compute discount factors along the swap path
    for (i=0;i<=iSwapVectorLength-1;++i){
      for(b=0;b<BLOCKSIZE;b++){
        pdSwapRatePath[i*BLOCKSIZE + b] =
          ppdHJMPath[iSwapStartTimeIndex][i*BLOCKSIZE + b];
      }
    }
    iSuccess = Discount_Factors_Blocking(pdSwapDiscountFactors, iSwapVectorLength, dSwapVectorYears, pdSwapRatePath, BLOCKSIZE);
    if (iSuccess!=1)
      return iSuccess;


    // ========================
    // Simulation
    for (b=0;b<BLOCKSIZE;b++){
      dFixedLegValue = 0.0;
      for (i=0;i<=iSwapVectorLength-1;++i){
        dFixedLegValue += pdSwapPayoffs[i]*pdSwapDiscountFactors[i*BLOCKSIZE + b];
      }
      dSwaptionPayoff = dMax(dFixedLegValue - 1.0, 0);

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

  //results returned
  pdSwaptionPrice[0] = dSimSwaptionMeanPrice;
  pdSwaptionPrice[1] = dSimSwaptionStdError;

  iSuccess = 1;
  return iSuccess;
}
