#pragma once
#ifdef __cplusplus
extern "C" {
#endif

double *dvector(size_t size);
void free_dvector(double *ptr);
double **dmatrix(size_t row_minus_1, size_t col_minus_1);
void free_dmatrix(double **ptr);

#ifdef __cplusplus
}
#endif
