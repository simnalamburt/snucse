#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

student_t student = { "2013-11392", "Hyeon Kim", "simnalamburt@gmail.com" };
void register_rotate_functions() { add_rotate_function(rotate, ""); }

void rotate(int dim, pixel *src, pixel *dst) {
  const int block = 32;
  const int dim_1 = dim - 1;

  int block_j;
  for (block_j = 0; block_j < dim; block_j += block) {
    int block_i;
    for (block_i = 0; block_i < dim; block_i += block) {
      int j;
      for (j = 0; j < block; ++j) {
        const int x = block_j + j;
        int i;
        for (i = 0; i < block; ++i) {
          const int y = block_i + i;
          dst[(dim_1 - x)*dim + y] = src[y*dim + x];
        }
      }
    }
  }
}
