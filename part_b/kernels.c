#include <stdio.h>
#include "defs.h"

student_t student = { "2013-11392", "Hyeon Kim", "simnalamburt@snu.ac.kr" };
void register_rotate_functions() {}
void rotate(int a, pixel *b, pixel *c) {}
void register_smooth_functions() { add_smooth_function(smooth, ""); }

static inline int min(int a, int b) { return a < b ? a : b; }
static inline int max(int a, int b) { return a > b ? a : b; }

void smooth(int size, pixel *src, pixel *dst) {
  size_t r, g, b;
  int row, col, x, y;
  for (row = 0; row < size; ++row) {
    for (col = 0; col < size; ++col) {
      r = g = b = 0;
      for (y = max(row - 1, 0); y < min(row + 2, size); ++y) {
        for (x = max(col - 1, 0); x < min(col + 2, size); ++x) {
          pixel *p = &src[y*size + x];
          r += p->red;
          g += p->green;
          b += p->blue;
        }
      }

      const size_t count = (min(row + 2, size) - max(row - 1, 0))*(min(col + 2, size) - max(col - 1, 0));

      pixel *p = &dst[row*size + col];
      p->red   = r/count;
      p->green = g/count;
      p->blue  = b/count;
    }
  }
}
