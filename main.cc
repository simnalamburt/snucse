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
  task_t tasks[TASKS];
  void init(task_t *task, int task_id);
}


int main() {
  auto time = system_clock::now();

  for (int task_id = 0; task_id < TASKS; ++task_id) {
    init(&tasks[task_id], task_id);

    for (int i = 0; i < ITERS; ++i) {
      swaption(&tasks[task_id], i);
    }

    double sum = 0;
    double square_sum = 0;
    for (int i = 0; i < ITERS; ++i) {
      sum += tasks[task_id].sums[i];
      square_sum += tasks[task_id].square_sums[i];
    }

    // Store results
    double mean = sum/TRIALS;
    double error = sqrt((square_sum - sum*sum/TRIALS)/(TRIALS - 1.0)/TRIALS);
    printf("Swaption%d: [SwaptionPrice: %.10lf StdError: %.10lf]\n", task_id, mean, error);
  }

  auto elapsed = duration<double>(system_clock::now() - time).count();
  cerr << "Total elapsed time : " << elapsed << " seconds" << endl;
  return 0;
}


namespace {
  //
  // Initialize buffers
  //
  void init(task_t *task, int task_id) {
    double *pdForward = task->forward;
    double *pdTotalDrift = task->drifts;
    double *seeds = task->seeds;
    double *pdSwapPayoffs = task->payoffs;
    double *sums = task->sums;
    double *square_sums = task->square_sums;


    // Mathmatical constants
    const double strike = (double)task_id/TASKS;
    const double dPaymentInterval = 1.0;
    const int iFreqRatio = dPaymentInterval/DELTA + 0.5;
    const double dTenor = 2.0;
    const int iSwapTimePoints = dTenor/DELTA + 0.5;


    // Store swap payoffs
    memset(pdSwapPayoffs, 0, sizeof pdSwapPayoffs);
    for (int i = iFreqRatio; i <= iSwapTimePoints; i += iFreqRatio) {
      double tmp = exp(strike*dPaymentInterval);
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
    pdForward[0] = pdYield[0];
    for (int i = 1; i < N; ++i) {
      pdForward[i] = (i + 1)*pdYield[i] - i*pdYield[i - 1];
    }

    // Computation of drifts from factor volatilities
    double ppdDrifts[FACTORS][N - 1];
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

    // Init seeds
    double seed = 100;
    for (int i = 0; i < ITERS; ++i) {
      seeds[i] = seed;
      seed += BLOCKSIZE*(N - 1)*FACTORS;
    }

    // Zerofill sums and square_sums
    memset(sums, 0, sizeof sums);
    memset(square_sums, 0, sizeof square_sums);
  }
}
