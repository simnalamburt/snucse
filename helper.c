#include <assert.h>
#include <stdlib.h>
#include "compute.h"


//
// allocate a double vector with subscript range v[nl..nh]
//
double *dvector(long nh) {
  double *v = (double*)malloc((size_t)((nh + 2)*sizeof(double)));
  assert(v);
  return v + 1;
}


//
// free a double vector allocated with dvector()
//
void free_dvector(double *v) {
  free((void*)(v - 1));
}


//
// allocate a double matrix with subscript range m[0..nrh][0..nch]
//
double **dmatrix(long nrh, long nch) {
  long nrow = nrh + 1, ncol = nch + 1;

  // allocate pointers to rows
  double **m = (double**)malloc((size_t)((nrow+1)*sizeof(double*)));
  assert(m);
  m += 1;

  // allocate rows and set pointers to them
  m[0] = (double*)malloc((size_t)((nrow*ncol+1)*sizeof(double)));
  assert(m[0]);
  m[0] += 1;

  for (long i = 1; i <= nrh; ++i) {
    m[i] = m[i-1] + ncol;
  }

  // return pointer to array of pointers to rows
  return m;
}


//
// free a double matrix allocated by dmatrix()
//
void free_dmatrix(double **m) {
  free((void*)(m[0] - 1));
  free((void*)(m - 1));
}
