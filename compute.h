#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

int swaption(double *pdSwaptionPrice, double dStrike, int iN, int iFactors, double *pdYield, double **ppdFactors, int BLOCKSIZE);

#ifdef __cplusplus
}
#endif
