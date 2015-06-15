#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

double *dvector(long nl, long nh);
void free_dvector(double *v, long nl);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long ncl);

#ifdef __cplusplus
}
#endif
