#include <stdlib.h>
#include <stdint.h>
#include "helper.h"


//
// Allocate/deallocate a vector
//
double *dvector(size_t size_minus_1) {
  const size_t size = size_minus_1 + 1;

  return malloc(size * sizeof(double));
}

void free_dvector(double *ptr) { free(ptr); }


//
// Allocate/deallocate a matrix
//
// Usage:
//     auto matrix = dmatrix(row - 1, col - 1);
//     matrix[0..row][0..col] = 30;
//
double **dmatrix(size_t row_minus_1, size_t col_minus_1) {
  const size_t col = col_minus_1 + 1;
  const size_t row = row_minus_1 + 1;

  // Allocate an array for a column
  double **m = malloc(row*sizeof(double*));
  uintptr_t mem = (uintptr_t)malloc(row*col*sizeof(double));

  // Allocate each row
  for (size_t i = 0; i < row; ++i) {
    m[i] = (double*)(mem + i*col*sizeof(double));
  }

  return m;
}

void free_dmatrix(double **m) {
  free(m[0]);
  free(m);
}
