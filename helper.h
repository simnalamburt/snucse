#pragma once
#include "type.h"

FTYPE *dvector(long nl, long nh );
void free_dvector(FTYPE *v, long nl);

FTYPE **dmatrix(long nrl, long nrh, long ncl, long nch);
void free_dmatrix(FTYPE **m, long nrl, long ncl);
