//
// RanUnif.c
//
// Author       : Mark Broadie
// Collaborator : Mikhail Smelyanskiy, Intel
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "type.h"

//
// Uniform random number generator
//
FTYPE RanUnif(long *s) {
  long ix = *s;
  *s = ix+1;
  ix *= 1513517L;
  ix %= 2147483647L;
  long k1 = ix/127773L;
  ix = 16807L*(ix - k1*127773L) - k1*2836L;
  if (ix < 0) { ix = ix + 2147483647L; }

  return ix * 4.656612875e-10;
}
