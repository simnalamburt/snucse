//
// MaxFunction.cpp
//
// Author: Mark Broadie
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "type.h"

FTYPE dMax( FTYPE dA, FTYPE dB )
{
  return (dA>dB ? dA:dB);
}
