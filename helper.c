#include <assert.h>
#include <stdlib.h>
#include "compute.h"


//
// allocate a double vector with subscript range v[nl..nh]
//
double *dvector(long nl, long nh) {
  double *v = (double*)malloc((size_t)((nh - nl + 2)*sizeof(double)));
  assert(v);
  return v - nl + 1;
}


//
// free a double vector allocated with dvector()
//
void free_dvector(double *v, long nl) {
  free((void*)(v + nl - 1));
}


//
// allocate a double matrix with subscript range m[nrl..nrh][ncl..nch]
//
double **dmatrix(long nrl, long nrh, long ncl, long nch) {
  long nrow = nrh - nrl + 1, ncol = nch - ncl + 1;

  // allocate pointers to rows
  double **m = (double**)malloc((size_t)((nrow+1)*sizeof(double*)));
  assert(m);
  m += 1;
  m -= nrl;

  // allocate rows and set pointers to them
  m[nrl] = (double*)malloc((size_t)((nrow*ncol+1)*sizeof(double)));
  assert(m[nrl]);
  m[nrl] += 1;
  m[nrl] -= ncl;

  for (long i = nrl + 1; i <= nrh; ++i) {
    m[i] = m[i-1] + ncol;
  }

  // return pointer to array of pointers to rows
  return m;
}


//
// free a double matrix allocated by dmatrix()
//
void free_dmatrix(double **m, long nrl, long ncl) {
  free((void*)(m[nrl] + ncl - 1));
  free((void*)(m + nrl - 1));
}
