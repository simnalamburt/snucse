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
#include <cstring>
#include <cmath>
#include <pthread.h>
#include "compute.h"

#define THREADS 16
#define TASKS 128

using namespace std;
using namespace chrono;


namespace {
  struct result_t { double mean, error; };
  result_t results[TASKS];


  //
  // Executed per task
  //
  void per_task(int task_id) {
    //
    // Mathmatical constants
    //
    const double dStrikeCont = (double)task_id/TASKS;
    const double dPaymentInterval = 1.0;
    const int iFreqRatio = dPaymentInterval/DELTA + 0.5;
    const double dMaturity = 1.0;
    const int iSwapVectorLength = N - dMaturity/DELTA + 0.5;
    const double dTenor = 2.0;
    const int iSwapTimePoints = dTenor/DELTA + 0.5;


    // Store swap payoffs
    double pdSwapPayoffs[iSwapVectorLength];
    memset(pdSwapPayoffs, 0, sizeof pdSwapPayoffs);
    for (int i = iFreqRatio; i <= iSwapTimePoints; i += iFreqRatio) {
      double tmp = exp(dStrikeCont*dPaymentInterval);
      // Normally, the bond pays coupon equal to this amount
      // But at terminal time point, bond pays coupon plus par amount
      pdSwapPayoffs[i] = i == iSwapTimePoints ? tmp : tmp - 1;
    }

    // Initialize yield curve
    double pdYield[N];
    double tmp = 0.1;
    for (int i = 0; i < N; ++i) {
      pdYield[i] = tmp;
      tmp += 0.005;
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
    double pdTotalDrift[N - 1];
    // Computation of factor drifts for shortest maturity
    for (int i = 0; i < FACTORS; ++i) {
      ppdDrifts[i][0] = 0.5*DELTA*factors[i][0]*factors[i][0];
    }
    // Computation of factor drifts for other maturities
    for (int i = 0; i < FACTORS; ++i) {
      for (int j = 1; j < N - 1; ++j) {
        double sum0 = 0;
        for(int l = 0; l < j; ++l) { sum0 -= ppdDrifts[i][l]; }
        ppdDrifts[i][j] = sum0;

        double sum = 0;
        for(int l = 0; l <= j; ++l) { sum += factors[i][l]; }
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
    double seeds[ITERS];
    double seed = 100;
    for (int i = 0; i < ITERS; ++i) {
      seeds[i] = seed;
      seed += BLOCKSIZE*(N - 1)*FACTORS;
    }

    double sums[ITERS] = {};
    double square_sums[ITERS] = {};

    swaption(pdForward, pdTotalDrift, seeds, pdSwapPayoffs, sums, square_sums);

    double sum = 0;
    double square_sum = 0;
    for (int i = 0; i < ITERS; ++i) {
      sum += sums[i];
      square_sum += square_sums[i];
    }

    // Store results
    results[task_id].mean = sum/TRIALS;
    results[task_id].error = sqrt((square_sum - sum*sum/TRIALS)/(TRIALS - 1.0)/TRIALS);
  }

  struct param_t { int begin, end; };
  void *worker(void *arg) {
    auto time = system_clock::now();

    param_t *param = (param_t*)arg;
    for (int i = param->begin; i < param->end; ++i) { per_task(i); }

    auto elapsed = duration<double>(system_clock::now() - time).count();
    cerr << "[" << param->begin << ", " << param->end << ") " << elapsed << " seconds" << endl;
    return NULL;
  }
}


int main() {
  auto time = system_clock::now();

  param_t params[THREADS];
  const int chunksize = TASKS/THREADS;
  for (int i = 0; i < THREADS; ++i) {
    params[i].begin = i*chunksize;
    params[i].end = i != THREADS - 1 ? (i + 1)*chunksize : TASKS;
  }

  pthread_t threads[THREADS];
  for (int i = 0; i < THREADS; ++i) {
    pthread_create(&threads[i], NULL, worker, &params[i]);
  }

  for (int i = 0; i < THREADS; ++i) {
    pthread_join(threads[i], NULL);
    for (int n = params[i].begin; n < params[i].end; ++n) {
      printf("Swaption%d: [SwaptionPrice: %.10lf StdError: %.10lf]\n", n, results[n].mean, results[n].error);
    }
  }

  auto elapsed = duration<double>(system_clock::now() - time).count();
  cerr << "Total elapsed time : " << elapsed << " seconds" << endl;
  return 0;
}
