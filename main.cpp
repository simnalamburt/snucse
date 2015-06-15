//
// main.cpp
//
// Authors      : Mark Broadie, Jatin Dewanwala
// Collaborator : Mikhail Smelyanskiy, Jike Chong, Intel
//
// Routines to compute various security prices using HJM framework (via Simulation).
//
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <pthread.h>
#include "helper.h"
#include "compute.h"


namespace {
  // Parameter struct for pthread workers
  typedef struct {
    int Id;
    double dSimSwaptionMeanPrice;
    double dSimSwaptionStdError;
    double dStrike;
    double dCompounding;
    double dMaturity;
    double dTenor;
    double dPaymentInterval;
    int iN;
    double dYears;
    int iFactors;
    double *pdYield;
    double **ppdFactors;
  } parm;


  //
  // Global constants
  //
  const int NUM_TRIALS = 1000000;
  const int nThreads = 16;
  const int nSwaptions = 128;


  //
  // Global variables
  //
  int iN = 11;
  double dYears = 5.5;
  int iFactors = 3;
  parm *swaptions;

  void *worker(void *arg) {
    int tid = *(int*)arg;
    const int chunksize = nSwaptions/nThreads;
    const int beg = tid*chunksize;
    const int end = tid != nThreads - 1 ? (tid + 1)*chunksize : nSwaptions;
    double pdSwaptionPrice[2];
    for (int i = beg; i < end; ++i) {
      int block_size = 16;
      int iSuccess = swaption(pdSwaptionPrice,  swaptions[i].dStrike,
          swaptions[i].dCompounding, swaptions[i].dMaturity,
          swaptions[i].dTenor, swaptions[i].dPaymentInterval,
          swaptions[i].iN, swaptions[i].iFactors, swaptions[i].dYears,
          swaptions[i].pdYield, swaptions[i].ppdFactors,
          100, NUM_TRIALS, block_size);
      assert(iSuccess == 1);
      swaptions[i].dSimSwaptionMeanPrice = pdSwaptionPrice[0];
      swaptions[i].dSimSwaptionStdError = pdSwaptionPrice[1];
    }
    return NULL;
  }
}




//
// Note: Whenever we type-cast to (int), we add 0.5 to ensure that the value is rounded to the correct number.
// For instance, if X/Y = 0.999 then (int) (X/Y) will equal 0 and not 1 (as (int) rounds down).
// Adding 0.5 ensures that this does not happen. Therefore we use (int) (X/Y + 0.5); instead of (int) (X/Y);
//
int main() {
  pthread_t *threads = (pthread_t*)malloc(nThreads*sizeof(pthread_t));

  pthread_attr_t pthread_custom_attr;
  pthread_attr_init(&pthread_custom_attr);

  // Initialize input dataset
  double **factors = dmatrix(0, iFactors-1, 0, iN-2);

  // The three rows store vol data for the three factors
  factors[0][0] = 0.01;
  factors[0][1] = 0.01;
  factors[0][2] = 0.01;
  factors[0][3] = 0.01;
  factors[0][4] = 0.01;
  factors[0][5] = 0.01;
  factors[0][6] = 0.01;
  factors[0][7] = 0.01;
  factors[0][8] = 0.01;
  factors[0][9] = 0.01;

  factors[1][0] = 0.009048;
  factors[1][1] = 0.008187;
  factors[1][2] = 0.007408;
  factors[1][3] = 0.006703;
  factors[1][4] = 0.006065;
  factors[1][5] = 0.005488;
  factors[1][6] = 0.004966;
  factors[1][7] = 0.004493;
  factors[1][8] = 0.004066;
  factors[1][9] = 0.003679;

  factors[2][0] = 0.001000;
  factors[2][1] = 0.000750;
  factors[2][2] = 0.000500;
  factors[2][3] = 0.000250;
  factors[2][4] = 0.000000;
  factors[2][5] = -0.000250;
  factors[2][6] = -0.000500;
  factors[2][7] = -0.000750;
  factors[2][8] = -0.001000;
  factors[2][9] = -0.001250;

  // Setting up multiple swaptions
  swaptions = (parm *)malloc(sizeof(parm)*nSwaptions);

  for (int i = 0; i < nSwaptions; i++) {
    swaptions[i].Id = i;
    swaptions[i].iN = iN;
    swaptions[i].iFactors = iFactors;
    swaptions[i].dYears = dYears;

    swaptions[i].dStrike =  (double)i / (double)nSwaptions;
    swaptions[i].dCompounding =  0;
    swaptions[i].dMaturity =  1;
    swaptions[i].dTenor =  2.0;
    swaptions[i].dPaymentInterval =  1.0;

    swaptions[i].pdYield = dvector(0,iN-1);;
    swaptions[i].pdYield[0] = .1;

    for (int j = 1; j <= swaptions[i].iN-1; ++j) {
      swaptions[i].pdYield[j] = swaptions[i].pdYield[j-1]+.005;
    }

    swaptions[i].ppdFactors = dmatrix(0, swaptions[i].iFactors-1, 0, swaptions[i].iN-2);
    for(int k = 0; k <= swaptions[i].iFactors-1; ++k) {
      for(int j = 0; j <= swaptions[i].iN-2; ++j) {
        swaptions[i].ppdFactors[k][j] = factors[k][j];
      }
    }
  }


  //
  // Calling the Swaption Pricing Routine
  //
  int threadIDs[nThreads];
  for (int i = 0; i < nThreads; ++i) {
    threadIDs[i] = i;
    pthread_create(&threads[i], &pthread_custom_attr, worker, &threadIDs[i]);
  }

  for (int i = 0; i < nThreads; ++i) {
    pthread_join(threads[i], NULL);
  }

  free(threads);

  for (int i = 0; i < nSwaptions; ++i) {
    printf("Swaption%d: [SwaptionPrice: %.10lf StdError: %.10lf]\n", i, swaptions[i].dSimSwaptionMeanPrice, swaptions[i].dSimSwaptionStdError);
  }

  for (int i = 0; i < nSwaptions; ++i) {
    free_dvector(swaptions[i].pdYield, 0);
    free_dmatrix(swaptions[i].ppdFactors, 0, 0);
  }

  free(swaptions);
  return 0;
}
