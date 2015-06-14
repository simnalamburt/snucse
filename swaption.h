#pragma once
#include "type.h"


int swaption(
    // Output vector that will store simulation results in the form:
    //     Swaption Price
    //     Swaption Standard Error
    //     Swaption Parameters
    FTYPE *pdSwaptionPrice,
    FTYPE dStrike,
    FTYPE dCompounding, // Compounding convention used for quoting the strike (0 => continuous, 0.5 => semi-annual, 1 => annual)
    FTYPE dMaturity, // Maturity of the swaption (time to expiration)
    FTYPE dTenor, // Tenor of the swap
    FTYPE dPaymentInterval, //frequency of swap payments e.g. dPaymentInterval = 0.5 implies a swap payment every half year

    // HJM Framework Parameters (please refer HJM.cpp for explanation of variables and functions)
    int iN,
    int iFactors,
    FTYPE dYears,
    FTYPE *pdYield,
    FTYPE **ppdFactors,

    // Simulation Parameters
    long iRndSeed, long lTrials, int blocksize, int tid);
