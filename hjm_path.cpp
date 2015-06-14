#include <math.h>
#include "helper.h"


namespace {
  //
  // Returns the inverse of cumulative normal distribution function.
  //
  // Reference: Moro, B., 1995, "The Full Monte," RISK (February), 57-58.
  //
  FTYPE cum_normal_inv(FTYPE u) {
    const FTYPE a[4] = { 2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637 };
    const FTYPE b[4] = { -8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833 };
    const FTYPE c[9] = {
      0.3374754822726147, 0.9761690190917186, 0.1607979714918209,
      0.0276438810333863, 0.0038405729373609, 0.0003951896511919,
      0.0000321767881768, 0.0000002888167364, 0.0000003960315187
    };

    FTYPE x = u - 0.5;
    FTYPE r;
    if (fabs (x) < 0.42) {
      r = x * x;
      r = x * ((( a[3]*r + a[2]) * r + a[1]) * r + a[0])/
            ((((b[3] * r+ b[2]) * r + b[1]) * r + b[0]) * r + 1.0);
      return r;
    }

    r = u;
    if (x > 0.0) { r = 1.0 - u; }
    r = log(-log(r));
    r = c[0] + r * (c[1] + r *
         (c[2] + r * (c[3] + r *
         (c[4] + r * (c[5] + r * (c[6] + r * (c[7] + r*c[8])))))));
    if (x < 0.0) { r = -r; }

    return r;
  }


  //
  // Uniform random number generator
  //
  FTYPE uniform_random(long *s) {
    long ix = *s;
    *s = ix+1;
    ix *= 1513517L;
    ix %= 2147483647L;
    long k1 = ix/127773L;
    ix = 16807L*(ix - k1*127773L) - k1*2836L;
    if (ix < 0) { ix = ix + 2147483647L; }

    return ix * 4.656612875e-10;
  }


  void serial_b(FTYPE **pdZ, FTYPE **randZ, int BLOCKSIZE, int iN, int iFactors) {
    for(int l = 0; l <= iFactors - 1; ++l){
      for(int b = 0; b < BLOCKSIZE; b++){
        for (int j = 1; j <= iN - 1; ++j){
          // 18% of the total executition time
          pdZ[l][BLOCKSIZE*j + b] = cum_normal_inv(randZ[l][BLOCKSIZE*j + b]);
        }
      }
    }
  }
}




//
// This function computes and stores an HJM Path for given inputs
//
int hjm_path(
    FTYPE **ppdHJMPath, // Matrix that stores generated HJM path (Output)
    int iN, // Number of time-steps
    int iFactors, // Number of factors in the HJM framework
    FTYPE dYears, // Number of years
    FTYPE *pdForward, // t=0 Forward curve
    FTYPE *pdTotalDrift, // Vector containing total drift corrections for different maturities
    FTYPE **ppdFactors, // Factor volatilities
    long *lRndSeed, // Random number seed
    int BLOCKSIZE)
{
  int iSuccess = 0;
  int i,j,l; //looping variables
  FTYPE **pdZ; //vector to store random normals
  FTYPE **randZ; //vector to store random normals
  FTYPE dTotalShock; //total shock by which the forward curve is hit at (t, T-t)
  FTYPE ddelt, sqrt_ddelt; //length of time steps

  ddelt = (FTYPE)(dYears/iN);
  sqrt_ddelt = sqrt(ddelt);

  pdZ   = dmatrix(0, iFactors-1, 0, iN*BLOCKSIZE -1); //assigning memory
  randZ = dmatrix(0, iFactors-1, 0, iN*BLOCKSIZE -1); //assigning memory


  // t=0 forward curve stored iN first row of ppdHJMPath
  // At time step 0: insert expected drift
  // rest reset to 0
  for (int b = 0; b < BLOCKSIZE; b++) {
    for (j = 0; j <= iN - 1; j++) {
      ppdHJMPath[0][BLOCKSIZE*j + b] = pdForward[j];

      // Initializing HJMPath to zero
      for (i = 1; i <= iN - 1; ++i) {
        ppdHJMPath[i][BLOCKSIZE*j + b] = 0;
      }
    }
  }


  //
  // Sequentially generating random numbers
  //
  for(int b=0; b<BLOCKSIZE; b++){
    for(int s=0; s<1; s++){
      for (j=1;j<=iN-1;++j){
        for (l=0;l<=iFactors-1;++l){
          //compute random number in exact same sequence
          randZ[l][BLOCKSIZE*j + b + s] = uniform_random(lRndSeed);  /* 10% of the total executition time */
        }
      }
    }
  }


  //
  // shocks to hit various factors for forward curve at t
  // 18% of the total executition time
  //
  serial_b(pdZ, randZ, BLOCKSIZE, iN, iFactors);


  //
  // Generation of HJM Path1
  //
  for(int b=0; b<BLOCKSIZE; b++){ // b is the blocks
    for (j=1;j<=iN-1;++j) {// j is the timestep

      for (l=0;l<=iN-(j+1);++l){ // l is the future steps
        dTotalShock = 0;

        for (i=0;i<=iFactors-1;++i){// i steps through the stochastic factors
          dTotalShock += ppdFactors[i][l]* pdZ[i][BLOCKSIZE*j + b];
        }

        ppdHJMPath[j][BLOCKSIZE*l+b] = ppdHJMPath[j-1][BLOCKSIZE*(l+1)+b]+ pdTotalDrift[l]*ddelt + sqrt_ddelt*dTotalShock;
        //as per formula
      }
    }
  } // end Blocks
  // -----------------------------------------------------

  free_dmatrix(pdZ, 0, iFactors -1, 0, iN*BLOCKSIZE -1);
  free_dmatrix(randZ, 0, iFactors -1, 0, iN*BLOCKSIZE -1);
  iSuccess = 1;
  return iSuccess;
}
