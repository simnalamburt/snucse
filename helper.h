#pragma once
#ifdef __cplusplus
extern "C" {
#endif

double *dvector(long nh);
void free_dvector(double *v);
double **dmatrix(long nrh, long nch);
void free_dmatrix(double **m);

#ifdef __cplusplus
}
#endif
