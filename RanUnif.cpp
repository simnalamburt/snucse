// RanUnif.c
// Author: Mark Broadie
// Collaborator: Mikhail Smelyanskiy, Intel


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "HJM_type.h"

FTYPE RanUnif( long *s );

FTYPE RanUnif( long *s )
{
  // uniform random number generator

  long   ix, k1;
  FTYPE dRes;
  
  ix = *s;
  k1 = ix/127773L;
  ix = 16807L*( ix - k1*127773L ) - k1 * 2836L;
  if (ix < 0) ix = ix + 2147483647L;
  *s   = ix;
  dRes = (ix * 4.656612875e-10);
  return (dRes);
  
} // end of RanUnif
