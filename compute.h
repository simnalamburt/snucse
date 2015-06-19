#pragma once
#ifdef __cplusplus
extern "C" {
#endif

//
// Contants
//
#define N 11
#define FACTORS 3

#define YEARS 5.5
#define DELTA (YEARS/N)

#define TRIALS 1000000
#define BLOCKSIZE 16
#define ITERS (TRIALS/BLOCKSIZE)

void swaption(
    const double * __restrict__ pdForward,
    const double * __restrict__ pdTotalDrift,
    const double * __restrict__ seeds,
    const double * __restrict__ pdSwapPayoffs,
    double * __restrict__ sums,
    double * __restrict__ square_sums);

static const double factors[FACTORS][N - 1] = {
  { 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01 },
  { 0.009048, 0.008187, 0.007408, 0.006703, 0.006065, 0.005488, 0.004966, 0.004493, 0.004066, 0.003679 },
  { 0.001000, 0.000750, 0.000500, 0.000250, 0.000000, -0.000250, -0.000500, -0.000750, -0.001000, -0.001250 }
};

#ifdef __cplusplus
}
#endif
