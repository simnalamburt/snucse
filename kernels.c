#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

student_t student = { "2013-11392", "Hyeon Kim", "simnalamburt@gmail.com" };
void register_rotate_functions() { add_rotate_function(rotate, ""); }

void rotate(int dim, pixel *src, pixel *dst) {
  const int block = 32;
  const int dim_1 = dim - 1;
  int block_i, block_j, i, j;

  for (block_i = 0; block_i < dim; block_i += block) {
    for (block_j = 0; block_j < dim; block_j += block) {
      const int i_end = block_i + block;
      for (i = block_i; i < i_end; ++i) {
        const int j_end = block_j + block;
        for (j = block_j; j < j_end; ++j) {
          dst[(dim_1 - i)*dim + j] = src[j*dim + i];
        }
      }
    }
  }
}
