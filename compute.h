#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define N 11
#define FACTORS 3

int swaption(double *pdSwaptionPrice, double dStrike, double *pdYield, double **ppdFactors, int BLOCKSIZE);

#ifdef __cplusplus
}
#endif
