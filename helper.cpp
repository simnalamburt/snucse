#include <stdio.h>
#include <stdlib.h>
#include "helper.h"


namespace {
  //
  // Numerical Recipes standard error handler
  //
  void nrerror(const char *error_text) {
    fprintf(stderr, "Numerical Recipes run-time error...\n");
    fprintf(stderr, "%s\n", error_text);
    fprintf(stderr, "...now exiting to system...\n");
    exit(1);
  }
}


//
// allocate a FTYPE vector with subscript range v[nl..nh]
//
FTYPE *dvector(long nl, long nh) {
  FTYPE *v = (FTYPE*)malloc((size_t)((nh - nl + 2)*sizeof(FTYPE)));
  if (!v) { nrerror("allocation failure in dvector()"); }
  return v - nl + 1;
}


//
// free a FTYPE vector allocated with dvector()
//
void free_dvector(FTYPE *v, long nl) {
  free((void*)(v + nl - 1));
}


//
// allocate a FTYPE matrix with subscript range m[nrl..nrh][ncl..nch]
//
FTYPE **dmatrix(long nrl, long nrh, long ncl, long nch) {
  long nrow = nrh - nrl + 1, ncol = nch - ncl + 1;

  // allocate pointers to rows
  FTYPE **m = (FTYPE**)malloc((size_t)((nrow+1)*sizeof(FTYPE*)));
  if (!m) { nrerror("allocation failure 1 in dmatrix()"); }
  m += 1;
  m -= nrl;

  // allocate rows and set pointers to them
  m[nrl] = (FTYPE*)malloc((size_t)((nrow*ncol+1)*sizeof(FTYPE)));
  if (!m[nrl]) { nrerror("allocation failure 2 in dmatrix()"); }
  m[nrl] += 1;
  m[nrl] -= ncl;

  for (long i = nrl + 1; i <= nrh; ++i) {
    m[i] = m[i-1] + ncol;
  }

  // return pointer to array of pointers to rows
  return m;
}


//
// free a FTYPE matrix allocated by dmatrix()
//
void free_dmatrix(FTYPE **m, long nrl, long ncl) {
  free((void*)(m[nrl] + ncl - 1));
  free((void*)(m + nrl - 1));
}
