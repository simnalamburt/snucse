#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "defs.h"

student_t student = { "2013-11392", "Hyeon Kim", "simnalamburt@snu.ac.kr" };
void register_rotate_functions() {}
void rotate(int a, pixel *b, pixel *c) {}


//
// Scan once
//
static void _scan_edge(const int size, pixel *const s0, pixel *const s1, pixel *const d) {
  uint32_t r = s0[0].red + s0[1].red +
               s1[0].red + s1[1].red;
  uint32_t g = s0[0].green + s0[1].green +
               s1[0].green + s1[1].green;
  uint32_t b = s0[0].blue + s0[1].blue +
               s1[0].blue + s1[1].blue;
  d[0].red   = r/4;
  d[0].green = g/4;
  d[0].blue  = b/4;

  int col;
  for (col = 1; col < size - 1; ++col) {
    r += s0[col+1].red   + s1[col+1].red;
    g += s0[col+1].green + s1[col+1].green;
    b += s0[col+1].blue  + s1[col+1].blue;
    d[col].red   = r/6;
    d[col].green = g/6;
    d[col].blue  = b/6;
    r -= s0[col-1].red   + s1[col-1].red;
    g -= s0[col-1].green + s1[col-1].green;
    b -= s0[col-1].blue  + s1[col-1].blue;
  }

  d[col].red   = r/4;
  d[col].green = g/4;
  d[col].blue  = b/4;
}

static void scan_once(int size, pixel *src, pixel *dst) {
  int row, col;
  for (row = 1; row < size - 1; ++row) {
    pixel *const s0 = &src[size*(row - 1)],
          *const s1 = &src[size*row],
          *const s2 = &src[size*(row + 1)],
          *const d  = &dst[size*row];
    uint32_t r = s0[0].red + s0[1].red +
                 s1[0].red + s1[1].red +
                 s2[0].red + s2[1].red;
    uint32_t g = s0[0].green + s0[1].green +
                 s1[0].green + s1[1].green +
                 s2[0].green + s2[1].green;
    uint32_t b = s0[0].blue + s0[1].blue +
                 s1[0].blue + s1[1].blue +
                 s2[0].blue + s2[1].blue;
    d[0].red   = r/6;
    d[0].green = g/6;
    d[0].blue  = b/6;

    for (col = 1; col < size - 1; ++col) {
      r += s0[col+1].red   + s1[col+1].red   + s2[col+1].red;
      g += s0[col+1].green + s1[col+1].green + s2[col+1].green;
      b += s0[col+1].blue  + s1[col+1].blue  + s2[col+1].blue;
      d[col].red   = r/9;
      d[col].green = g/9;
      d[col].blue  = b/9;
      r -= s0[col-1].red   + s1[col-1].red   + s2[col-1].red;
      g -= s0[col-1].green + s1[col-1].green + s2[col-1].green;
      b -= s0[col-1].blue  + s1[col-1].blue  + s2[col-1].blue;
    }

    d[col].red   = r/6;
    d[col].green = g/6;
    d[col].blue  = b/6;
  }

  _scan_edge(size, src, &src[size], dst);
  _scan_edge(size, &src[size*(size - 2)], &src[size*(size - 1)], &dst[size*(size - 1)]);
}


//
// Scan twice
//
static void scan_twice(int size, pixel *src, pixel *dst) {
  typedef struct { uint32_t r, g, b; } temp_t;
  temp_t *tmp = malloc(size * size * sizeof(temp_t));
  uint32_t r, g, b;
  int row, col;

  // Scan row
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

    t[col].r = r*3;
    t[col].g = g*3;
    t[col].b = b*3;
  }

  // Scan column
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


//
// Both
//
void smooth(int size, pixel *src, pixel *dst) {
  if (size >= 256) {
    scan_once(size, src, dst);
  } else {
    scan_twice(size, src, dst);
  }
}

void register_smooth_functions() {
  add_smooth_function(scan_once, "Scan everything at once");
  add_smooth_function(scan_twice, "Scan row and column separately");
  add_smooth_function(smooth, "Use both methods");
}
