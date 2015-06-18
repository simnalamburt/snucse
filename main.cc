//
// main.cpp
//
// Authors      : Mark Broadie, Jatin Dewanwala
// Collaborator : Mikhail Smelyanskiy, Jike Chong, Intel
//
// Routines to compute various security prices using HJM framework (via Simulation).
//
#include <iostream>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <pthread.h>
#include "helper.h"
#include "compute.h"

using namespace std;
using namespace chrono;


namespace {
  // Parameter struct for pthread workers
  struct param_t {
    int Id;
    double *pdYield;
    double **ppdFactors;
    double result_mean;
    double result_error;
  };


  //
  // Global constants
  //
  const int nThreads = 16;
  const int nSwaptions = 128;
  const int iN = 11;
  const int iFactors = 3;


  //
  // Global variables
  //
  param_t *swaptions;
  void *worker(void *arg) {
    auto time = system_clock::now();

    int tid = *(int*)arg;
    const int chunksize = nSwaptions/nThreads;
    const int begin = tid*chunksize;
    const int end = tid != nThreads - 1 ? (tid + 1)*chunksize : nSwaptions;
    double result[2];
    for (int i = begin; i < end; ++i) {
      int block_size = 16;
      int iSuccess = swaption(result, (double)swaptions[i].Id/(double)nSwaptions,
          iN, iFactors, swaptions[i].pdYield, swaptions[i].ppdFactors, block_size);
      assert(iSuccess == 1);
      swaptions[i].result_mean = result[0];
      swaptions[i].result_error = result[1];
    }

    auto elapsed = duration<double>(system_clock::now() - time).count();
    cerr << "Thread " << tid << ", " << elapsed << " seconds" << endl;
    return NULL;
  }
}




//
// Note: Whenever we type-cast to (int), we add 0.5 to ensure that the value is rounded to the correct number.
// For instance, if X/Y = 0.999 then (int) (X/Y) will equal 0 and not 1 (as (int) rounds down).
// Adding 0.5 ensures that this does not happen. Therefore we use (int) (X/Y + 0.5); instead of (int) (X/Y);
//
int main() {
  auto time = system_clock::now();

  // Initialize input dataset
  double **factors = dmatrix(iFactors, iN - 1);

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
  swaptions = new param_t[nSwaptions];

  for (int i = 0; i < nSwaptions; i++) {
    swaptions[i].Id = i;
    swaptions[i].pdYield = dvector(iN);
    swaptions[i].pdYield[0] = .1;

    for (int j = 1; j <= iN-1; ++j) {
      swaptions[i].pdYield[j] = swaptions[i].pdYield[j-1]+.005;
    }

    swaptions[i].ppdFactors = dmatrix(iFactors, iN - 1);
    for(int k = 0; k <= iFactors-1; ++k) {
      for(int j = 0; j <= iN-2; ++j) {
        swaptions[i].ppdFactors[k][j] = factors[k][j];
      }
    }
  }


  //
  // Calling the Swaption Pricing Routine
  //
  pthread_t *threads = (pthread_t*)malloc(nThreads*sizeof(pthread_t));

  int threadIDs[nThreads];
  for (int i = 0; i < nThreads; ++i) {
    threadIDs[i] = i;
    pthread_create(&threads[i], NULL, worker, &threadIDs[i]);
  }

  for (int i = 0; i < nThreads; ++i) {
    pthread_join(threads[i], NULL);
  }

  free(threads);

  for (int i = 0; i < nSwaptions; ++i) {
    printf("Swaption%d: [SwaptionPrice: %.10lf StdError: %.10lf]\n",
        i, swaptions[i].result_mean, swaptions[i].result_error);
  }

  for (int i = 0; i < nSwaptions; ++i) {
    free_dvector(swaptions[i].pdYield);
    free_dmatrix(swaptions[i].ppdFactors);
  }

  delete[] swaptions;
  free_dmatrix(factors);

  auto elapsed = duration<double>(system_clock::now() - time).count();
  cerr << "Total elapsed time : " << elapsed << " seconds" << endl;
  return 0;
}
