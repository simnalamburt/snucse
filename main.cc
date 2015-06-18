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
#include <pthread.h>
#include "compute.h"

#define THREADS 16
#define SWAPTIONS 128

using namespace std;
using namespace chrono;


namespace {
  struct param_t {
    int begin;
    int end;
  };

  struct task_t {
    int Id;
    double pdYield[N];
    double ppdFactors[FACTORS][N - 1];
    double result_mean;
    double result_error;
  };

  task_t swaptions[SWAPTIONS];

  void *worker(void *arg) {
    param_t *param = (param_t*)arg;

    auto time = system_clock::now();
    for (int i = param->begin; i < param->end; ++i) {
      double result[2];
      swaption(result, (double)swaptions[i].Id/(double)SWAPTIONS, swaptions[i].pdYield, swaptions[i].ppdFactors);
      swaptions[i].result_mean = result[0];
      swaptions[i].result_error = result[1];
    }
    auto elapsed = duration<double>(system_clock::now() - time).count();

    cerr << "[" << param->begin << ", " << param->end << ") " << elapsed << " seconds" << endl;
    return NULL;
  }
}


int main() {
  auto time = system_clock::now();

  //
  // Initialize input dataset
  //
  const double factors[FACTORS][N - 1] = {
    { 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01 },
    { 0.009048, 0.008187, 0.007408, 0.006703, 0.006065, 0.005488, 0.004966, 0.004493, 0.004066, 0.003679 },
    { 0.001000, 0.000750, 0.000500, 0.000250, 0.000000, -0.000250, -0.000500, -0.000750, -0.001000, -0.001250 }
  };

  for (int i = 0; i < SWAPTIONS; i++) {
    swaptions[i].Id = i;
    swaptions[i].pdYield[0] = .1;

    for (int j = 1; j < N; ++j) {
      swaptions[i].pdYield[j] = swaptions[i].pdYield[j-1]+.005;
    }

    for (int k = 0; k < FACTORS; ++k) {
      for (int j = 0; j < N - 1; ++j) {
        swaptions[i].ppdFactors[k][j] = factors[k][j];
      }
    }
  }


  //
  // Calling the Swaption Pricing Routine
  //
  param_t params[THREADS];
  const int chunksize = SWAPTIONS/THREADS;
  for (int i = 0; i < THREADS; ++i) {
    params[i].begin = i*chunksize;
    params[i].end = i != THREADS - 1 ? (i + 1)*chunksize : SWAPTIONS;
  }

  pthread_t threads[THREADS];
  for (int i = 0; i < THREADS; ++i) {
    pthread_create(&threads[i], NULL, worker, &params[i]);
  }

  for (int i = 0; i < THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  for (int i = 0; i < SWAPTIONS; ++i) {
    printf("Swaption%d: [SwaptionPrice: %.10lf StdError: %.10lf]\n", i, swaptions[i].result_mean, swaptions[i].result_error);
  }

  auto elapsed = duration<double>(system_clock::now() - time).count();
  cerr << "Total elapsed time : " << elapsed << " seconds" << endl;
  return 0;
}
