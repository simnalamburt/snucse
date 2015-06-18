#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define N 11
#define FACTORS 3

void swaption(
    double * __restrict__ result,
    double dStrike,
    const double * __restrict__ pdYield,
    const double ppdFactors[FACTORS][N - 1]);

#ifdef __cplusplus
}
#endif
