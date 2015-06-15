#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

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
