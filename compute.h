#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define N 11
#define FACTORS 3

void swaption(
    double * __restrict__ mean,
    double * __restrict__ error,
    double dStrike);

#ifdef __cplusplus
}
#endif
