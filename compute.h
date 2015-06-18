#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define N 11
#define FACTORS 3
#define BLOCKSIZE 16

int swaption(double *pdSwaptionPrice, double dStrike, double pdYield[N], double ppdFactors[FACTORS][N - 1]);

#ifdef __cplusplus
}
#endif
