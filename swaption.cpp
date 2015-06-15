//
// swaption.cpp
//
// Authors      : Mark Broadie, Jatin Dewanwala
// Collaborator : Mikhail Smelyanskiy, Intel, Jike Chong (Berkeley)
//
// Routines to compute various security prices using HJM framework (via Simulation).
//
#include <cstring>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "compute.h"


static inline int Discount_Factors_Blocking(double *pdDiscountFactors, int iN, double dYears, double *pdRatePath, int BLOCKSIZE) {
  int i,j,b;				//looping variables
  int iSuccess;			//return variable

  double ddelt;			//HJM time-step length
  ddelt = (double) (dYears/iN);

  double *pdexpRes;
  pdexpRes = dvector(0,(iN-1)*BLOCKSIZE-1);
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

  free_dvector(pdexpRes, 0);
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
  // ppdHJMPath = dmatrix(0,iN-1,0,iN-1);
  ppdHJMPath = dmatrix(0,iN-1,0,iN*BLOCKSIZE-1);    // **** per Trial data **** //
  pdForward = dvector(0, iN-1);
  ppdDrifts = dmatrix(0, iFactors-1, 0, iN-2);
  pdTotalDrift = dvector(0, iN-2);

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
  pdPayoffDiscountFactors = dvector(0, iN*BLOCKSIZE-1);
  pdDiscountingRatePath = dvector(0, iN*BLOCKSIZE-1);
  // *******************************

  iSwapVectorLength = (int) (iN - dMaturity/ddelt + 0.5);	//This is the length of the HJM rate path at the time index
  //corresponding to swaption maturity.
  // *******************************
  pdSwapRatePath = dvector(0, iSwapVectorLength*BLOCKSIZE - 1);
  pdSwapDiscountFactors  = dvector(0, iSwapVectorLength*BLOCKSIZE - 1);
  // *******************************
  pdSwapPayoffs = dvector(0, iSwapVectorLength - 1);


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
