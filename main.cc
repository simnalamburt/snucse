#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>
#include <cmath>
#include <pthread.h>
#include <CL/cl.h>
#include "compute.h"

#define THREADS 16
#define TASKS 128

using namespace std;
using namespace chrono;


namespace {
  task_t tasks[TASKS];
  result_t results[TASKS];
  void init(task_t *task, int task_id);
  void check(cl_int);
}


int main() {
  auto time = system_clock::now();

  //
  // OpenCL
  //
  cl_platform_id platform;
  check(clGetPlatformIDs(1, &platform, NULL));

  cl_device_type type = CL_DEVICE_TYPE_ALL;
  // Get device count
  cl_uint device_count;
  check(clGetDeviceIDs(platform, type, 0, NULL, &device_count));

  // Get all devices
  auto devices = unique_ptr<cl_device_id[]>(new cl_device_id[device_count]);
  check(clGetDeviceIDs(platform, type, device_count, devices.get(), NULL));

  // create a single context for all devices
  cl_int e;
  auto ctxt = clCreateContext(NULL, device_count, devices.get(), NULL, NULL, &e); check(e);

  // for each device create a separate queue
  auto cmdqs = unique_ptr<cl_command_queue[]>(new cl_command_queue[device_count]);
  for (size_t i = 0; i < device_count; ++i) {
    cmdqs[i] = clCreateCommandQueue(ctxt, devices[i], 0, &e); check(e);
  }

  auto buffer_tasks = clCreateBuffer(ctxt, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof tasks, tasks, &e); check(e);
  auto buffer_results = clCreateBuffer(ctxt, CL_MEM_WRITE_ONLY, sizeof results, NULL, &e); check(e);


  for (int task_id = 0; task_id < TASKS; ++task_id) {
    init(&tasks[task_id], task_id);
  }

  for (int task_id = 0; task_id < TASKS; ++task_id) {
    for (int i = 0; i < ITERS; ++i) {
      swaption(&tasks[task_id], &results[task_id], i);
    }
  }

  for (int task_id = 0; task_id < TASKS; ++task_id) {
    double sum = 0;
    double square_sum = 0;
    for (int i = 0; i < ITERS; ++i) {
      sum += results[task_id].sums[i];
      square_sum += results[task_id].square_sums[i];
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
  }

  const char *clGetErrorMessage(cl_int error_code) {
    switch (error_code) {
    // run-time and JIT compiler errors
    case 0: return "CL_SUCCESS";
    case -1: return "CL_DEVICE_NOT_FOUND";
    case -2: return "CL_DEVICE_NOT_AVAILABLE";
    case -3: return "CL_COMPILER_NOT_AVAILABLE";
    case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case -5: return "CL_OUT_OF_RESOURCES";
    case -6: return "CL_OUT_OF_HOST_MEMORY";
    case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case -8: return "CL_MEM_COPY_OVERLAP";
    case -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case -11: return "CL_BUILD_PROGRAM_FAILURE";
    case -12: return "CL_MAP_FAILURE";
    case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case -16: return "CL_LINKER_NOT_AVAILABLE";
    case -17: return "CL_LINK_PROGRAM_FAILURE";
    case -18: return "CL_DEVICE_PARTITION_FAILED";
    case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // compile-time errors
    case -30: return "CL_INVALID_VALUE";
    case -31: return "CL_INVALID_DEVICE_TYPE";
    case -32: return "CL_INVALID_PLATFORM";
    case -33: return "CL_INVALID_DEVICE";
    case -34: return "CL_INVALID_CONTEXT";
    case -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case -36: return "CL_INVALID_COMMAND_QUEUE";
    case -37: return "CL_INVALID_HOST_PTR";
    case -38: return "CL_INVALID_MEM_OBJECT";
    case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case -40: return "CL_INVALID_IMAGE_SIZE";
    case -41: return "CL_INVALID_SAMPLER";
    case -42: return "CL_INVALID_BINARY";
    case -43: return "CL_INVALID_BUILD_OPTIONS";
    case -44: return "CL_INVALID_PROGRAM";
    case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case -46: return "CL_INVALID_KERNEL_NAME";
    case -47: return "CL_INVALID_KERNEL_DEFINITION";
    case -48: return "CL_INVALID_KERNEL";
    case -49: return "CL_INVALID_ARG_INDEX";
    case -50: return "CL_INVALID_ARG_VALUE";
    case -51: return "CL_INVALID_ARG_SIZE";
    case -52: return "CL_INVALID_KERNEL_ARGS";
    case -53: return "CL_INVALID_WORK_DIMENSION";
    case -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case -56: return "CL_INVALID_GLOBAL_OFFSET";
    case -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case -58: return "CL_INVALID_EVENT";
    case -59: return "CL_INVALID_OPERATION";
    case -60: return "CL_INVALID_GL_OBJECT";
    case -61: return "CL_INVALID_BUFFER_SIZE";
    case -62: return "CL_INVALID_MIP_LEVEL";
    case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case -64: return "CL_INVALID_PROPERTY";
    case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case -66: return "CL_INVALID_COMPILER_OPTIONS";
    case -67: return "CL_INVALID_LINKER_OPTIONS";
    case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // extension errors
    case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    default: return "Unknown OpenCL error";
    }
  }

  void check(cl_int err) {
    if (err == CL_SUCCESS) { return; }
    cerr << clGetErrorMessage(err) << endl;
    exit(1);
  }
}
