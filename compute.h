#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define N 11
#define FACTORS 3
#define BLOCKSIZE 16

int swaption(double *pdSwaptionPrice, double dStrike, double *pdYield, double **ppdFactors);

#ifdef __cplusplus
}
#endif
