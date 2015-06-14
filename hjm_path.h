#pragma once
#include "type.h"

int hjm_path(FTYPE **ppdHJMPath, int iN, int iFactors, FTYPE dYears, FTYPE *pdForward, FTYPE *pdTotalDrift, FTYPE **ppdFactors, long *lRndSeed, int BLOCKSIZE);
