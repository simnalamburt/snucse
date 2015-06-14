//
// main.cpp
//
// Authors      : Mark Broadie, Jatin Dewanwala
// Collaborator : Mikhail Smelyanskiy, Jike Chong, Intel
//
// Routines to compute various security prices using HJM framework (via Simulation).
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "nr_routines.h"
#include "HJM.h"
#include "main.h"
#include "type.h"

#ifdef ENABLE_THREADS
#include <pthread.h>
#define MAX_THREAD 1024
#endif //ENABLE_THREADS

#ifdef ENABLE_PARSEC_HOOKS
#include <hooks.h>
#endif


//
// Global variables
//
int NUM_TRIALS = DEFAULT_NUM_TRIALS;
int nThreads = 1;
int nSwaptions = 1;
int iN = 11;
FTYPE dYears = 5.5;
int iFactors = 3;
parm *swaptions;

// =================================================
FTYPE *dSumSimSwaptionPrice_global_ptr;
FTYPE *dSumSquareSimSwaptionPrice_global_ptr;
int chunksize;


void *worker(void *arg) {
  int tid = *(int*)arg;
  const int chunksize = nSwaptions/nThreads;
  const int beg = tid*chunksize;
  const int end = tid != nThreads - 1 ? (tid + 1)*chunksize : nSwaptions;
  FTYPE pdSwaptionPrice[2];
  for (int i = beg; i < end; ++i) {
    int iSuccess = HJM_Swaption_Blocking(pdSwaptionPrice,  swaptions[i].dStrike,
        swaptions[i].dCompounding, swaptions[i].dMaturity,
        swaptions[i].dTenor, swaptions[i].dPaymentInterval,
        swaptions[i].iN, swaptions[i].iFactors, swaptions[i].dYears,
        swaptions[i].pdYield, swaptions[i].ppdFactors,
        100, NUM_TRIALS, BLOCK_SIZE, 0);
    assert(iSuccess == 1);
    swaptions[i].dSimSwaptionMeanPrice = pdSwaptionPrice[0];
    swaptions[i].dSimSwaptionStdError = pdSwaptionPrice[1];
  }
  return NULL;
}




//
// Note: Whenever we type-cast to (int), we add 0.5 to ensure that the value is rounded to the correct number.
// For instance, if X/Y = 0.999 then (int) (X/Y) will equal 0 and not 1 (as (int) rounds down).
// Adding 0.5 ensures that this does not happen. Therefore we use (int) (X/Y + 0.5); instead of (int) (X/Y);
//
int main(int argc, char *argv[]) {
  int iSuccess = 0;

  FTYPE **factors=NULL;

#ifdef PARSEC_VERSION
#define __PARSEC_STRING(x) #x
#define __PARSEC_XSTRING(x) __PARSEC_STRING(x)
  printf("PARSEC Benchmark Suite Version "__PARSEC_XSTRING(PARSEC_VERSION)"\n");
  fflush(NULL);
#else
  printf("PARSEC Benchmark Suite\n");
  fflush(NULL);
#endif //PARSEC_VERSION
#ifdef ENABLE_PARSEC_HOOKS
  __parsec_bench_begin(__parsec_swaptions);
#endif

  if (argc == 1) {
    fprintf(stderr,
        " usage: \n"
        "\t-ns [number of swaptions (should be > number of threads]\n"
        "\t-sm [number of simulations]\n"
        "\t-nt [number of threads]\n");
    exit(1);
  }

  for (int j = 1; j < argc; ++j) {
    if (!strcmp("-sm", argv[j])) { NUM_TRIALS = atoi(argv[++j]); }
    else if (!strcmp("-nt", argv[j])) { nThreads = atoi(argv[++j]); }
    else if (!strcmp("-ns", argv[j])) { nSwaptions = atoi(argv[++j]); }
    else {
      fprintf(stderr,
          " usage: \n"
          "\t-ns [number of swaptions (should be > number of threads]\n"
          "\t-sm [number of simulations]\n"
          "\t-nt [number of threads]\n");
    }
  }

  if(nSwaptions < nThreads) {
    nSwaptions = nThreads;
  }

  printf("Number of Simulations: %d,  Number of threads: %d Number of swaptions: %d\n", NUM_TRIALS, nThreads, nSwaptions);

#ifdef ENABLE_THREADS
  pthread_t      *threads;
  pthread_attr_t  pthread_custom_attr;

  if ((nThreads < 1) || (nThreads > MAX_THREAD))
  {
    fprintf(stderr,"Number of threads must be between 1 and %d.\n", MAX_THREAD);
    exit(1);
  }
  threads = (pthread_t *) malloc(nThreads * sizeof(pthread_t));
  pthread_attr_init(&pthread_custom_attr);


  if ((nThreads < 1) || (nThreads > MAX_THREAD))
  {
    fprintf(stderr,"Number of threads must be between 1 and %d.\n", MAX_THREAD);
    exit(1);
  }

#else
  if (nThreads != 1)
  {
    fprintf(stderr,"Number of threads must be 1 (serial version)\n");
    exit(1);
  }
#endif //ENABLE_THREADS

  // initialize input dataset
  factors = dmatrix(0, iFactors-1, 0, iN-2);
  //the three rows store vol data for the three factors
  factors[0][0]= 0.01;
  factors[0][1]= 0.01;
  factors[0][2]= 0.01;
  factors[0][3]= 0.01;
  factors[0][4]= 0.01;
  factors[0][5]= 0.01;
  factors[0][6]= 0.01;
  factors[0][7]= 0.01;
  factors[0][8]= 0.01;
  factors[0][9]= 0.01;

  factors[1][0]= 0.009048;
  factors[1][1]= 0.008187;
  factors[1][2]= 0.007408;
  factors[1][3]= 0.006703;
  factors[1][4]= 0.006065;
  factors[1][5]= 0.005488;
  factors[1][6]= 0.004966;
  factors[1][7]= 0.004493;
  factors[1][8]= 0.004066;
  factors[1][9]= 0.003679;

  factors[2][0]= 0.001000;
  factors[2][1]= 0.000750;
  factors[2][2]= 0.000500;
  factors[2][3]= 0.000250;
  factors[2][4]= 0.000000;
  factors[2][5]= -0.000250;
  factors[2][6]= -0.000500;
  factors[2][7]= -0.000750;
  factors[2][8]= -0.001000;
  factors[2][9]= -0.001250;

  // setting up multiple swaptions
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
#ifdef ENABLE_PARSEC_HOOKS
  __parsec_roi_begin();
#endif

#ifdef ENABLE_THREADS
  int threadIDs[nThreads];
  for (int i = 0; i < nThreads; ++i) {
    threadIDs[i] = i;
    pthread_create(&threads[i], &pthread_custom_attr, worker, &threadIDs[i]);
  }
  for (int i = 0; i < nThreads; ++i) {
    pthread_join(threads[i], NULL);
  }

  free(threads);
#else
  int threadID=0;
  worker(&threadID);
#endif //ENABLE_THREADS

#ifdef ENABLE_PARSEC_HOOKS
  __parsec_roi_end();
#endif

  for (int i = 0; i < nSwaptions; ++i) {
    fprintf(stderr, "Swaption%d: [SwaptionPrice: %.10lf StdError: %.10lf] \n",
        i, swaptions[i].dSimSwaptionMeanPrice, swaptions[i].dSimSwaptionStdError);

  }

  for (int i = 0; i < nSwaptions; ++i) {
    free_dvector(swaptions[i].pdYield, 0, swaptions[i].iN-1);
    free_dmatrix(swaptions[i].ppdFactors, 0, swaptions[i].iFactors-1, 0, swaptions[i].iN-2);
  }


  free(swaptions);

  // -----------------------------------------------------------

#ifdef ENABLE_PARSEC_HOOKS
  __parsec_bench_end();
#endif
  return iSuccess;
}
