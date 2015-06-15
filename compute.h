#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

double *dvector(long nl, long nh);
void free_dvector(double *v, long nl);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long ncl);

int hjm_path(double **ppdHJMPath,
    int iN,
    int iFactors,
    double dYears,
    double *pdForward,
    double *pdTotalDrift,
    double **ppdFactors,
    long *lRndSeed,
    int BLOCKSIZE);

int swaption(
    // Output vector that will store simulation results in the form:
    //     Swaption Price
    //     Swaption Standard Error
    //     Swaption Parameters
    double *pdSwaptionPrice,
    double dStrike,
    double dCompounding, // Compounding convention used for quoting the strike (0 => continuous, 0.5 => semi-annual, 1 => annual)
    double dMaturity, // Maturity of the swaption (time to expiration)
    double dTenor, // Tenor of the swap
    double dPaymentInterval, //frequency of swap payments e.g. dPaymentInterval = 0.5 implies a swap payment every half year

    // HJM Framework Parameters (please refer HJM.cpp for explanation of variables and functions)
    int iN,
    int iFactors,
    double dYears,
    double *pdYield,
    double **ppdFactors,

    // Simulation Parameters
    long iRndSeed, long lTrials, int blocksize);

#ifdef __cplusplus
}
#endif
