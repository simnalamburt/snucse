#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "defs.h"

student_t student = { "2013-11392", "Hyeon Kim", "simnalamburt@snu.ac.kr" };
void register_rotate_functions() {}
void rotate(int a, pixel *b, pixel *c) {}
void register_smooth_functions() { add_smooth_function(smooth, ""); }

typedef struct { uint32_t r, g, b; } temp_t;

void smooth(int size, pixel *src, pixel *dst) {
  temp_t *tmp = malloc(size * size * sizeof(temp_t));
  uint32_t r, g, b;
  int row, col;

  // Pass 1
  for (row = 0; row < size; ++row) {
    pixel *const p = &src[row*size];
    temp_t *const t = &tmp[row*size];

    r = p[0].red   + p[1].red;
    g = p[0].green + p[1].green;
    b = p[0].blue  + p[1].blue;

    t[0].r = r*3;
    t[0].g = g*3;
    t[0].b = b*3;

    for (col = 1; col < size-1; ++col) {
      r += p[col+1].red;
      g += p[col+1].green;
      b += p[col+1].blue;

      t[col].r = r*2;
      t[col].g = g*2;
      t[col].b = b*2;

      r -= p[col-1].red;
      g -= p[col-1].green;
      b -= p[col-1].blue;
    }

    t[size-1].r = r*3;
    t[size-1].g = g*3;
    t[size-1].b = b*3;
  }

  // Pass 2
  {
    temp_t *const t = tmp;
    pixel *const d = dst;
    for (col = 0; col < size; ++col) {
      d[col].red   = (t[col].r + t[col + size].r)/2/6;
      d[col].green = (t[col].g + t[col + size].g)/2/6;
      d[col].blue  = (t[col].b + t[col + size].b)/2/6;
    }
  }

  for (row = 1; row < size-1; ++row) {
    temp_t *const t = &tmp[row*size];
    pixel *const d = &dst[row*size];
    for (col = 0; col < size; ++col) {
      d[col].red   = (t[col - size].r + t[col].r + t[col + size].r)/3/6;
      d[col].green = (t[col - size].g + t[col].g + t[col + size].g)/3/6;
      d[col].blue  = (t[col - size].b + t[col].b + t[col + size].b)/3/6;
    }
  }

  {
    temp_t *const t = &tmp[(size - 1)*size];
    pixel *const d = &dst[(size - 1)*size];
    for (col = 0; col < size; ++col) {
      d[col].red   = (t[col - size].r + t[col].r)/2/6;
      d[col].green = (t[col - size].g + t[col].g)/2/6;
      d[col].blue  = (t[col - size].b + t[col].b)/2/6;
    }
  }

  free(tmp);
}
