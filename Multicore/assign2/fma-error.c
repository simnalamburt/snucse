#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // prevent opti
  double one = argc < 2 ? 1.0 : atof(argv[1]);

  double a = one + 0x1.0p-51; // 1 + 2**-51
  double b = one - 0x1.0p-51; // 1 - 2**-51
  double c = -one;

  a = a*b + c;

  printf("%lf\n", a);
  printf("%lx\n", *(long*)(&a));
}
