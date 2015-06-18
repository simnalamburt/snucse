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
#include <pthread.h>
#include "compute.h"

#define THREADS 16
#define TASKS 128

using namespace std;
using namespace chrono;


namespace {
  struct param_t {
    int begin;
    int end;
  };

  struct task_t {
    double result_mean;
    double result_error;
  };

  task_t tasks[TASKS];


  void *worker(void *arg) {
    auto time = system_clock::now();

    param_t *param = (param_t*)arg;
    for (int i = param->begin; i < param->end; ++i) {
      //
      // Initialize
      //
      double pdYield[N];
      double tmp = 0.1;
      for (int j = 0; j < N; ++j) {
        pdYield[j] = tmp;
        tmp += 0.005;
      }


      //
      // Calculate
      //
      swaption(&tasks[i].result_mean, &tasks[i].result_error, (double)i/(double)TASKS, pdYield);
    }
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
      printf("Swaption%d: [SwaptionPrice: %.10lf StdError: %.10lf]\n", n, tasks[n].result_mean, tasks[n].result_error);
    }
  }

  auto elapsed = duration<double>(system_clock::now() - time).count();
  cerr << "Total elapsed time : " << elapsed << " seconds" << endl;
  return 0;
}
