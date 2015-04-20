#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

student_t student = { "2013-11392", "Hyeon Kim", "simnalamburt@gmail.com" };
void register_rotate_functions() { add_rotate_function(rotate, ""); }

void rotate(int dim, pixel *src, pixel *dst) {
  int i;
  for (i = 0; i < dim; ++i) {
    int j;
    for (j = 0; j < dim; ++j) {
      dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
    }
  }
}
