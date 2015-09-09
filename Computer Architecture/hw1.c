#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/// Qestion 2
void test1(unsigned short a) {
  printf("%04X\n", a);
}

/// Qestion 3
void f(bool a) { printf("%d\n", a); }

/// Qestion 4
int f1(unsigned w) { return (int)((w<<26)>>26); }
int f2(unsigned w) { return ((int)w<<26)>>26; }

void test2(unsigned a) {
  printf("%x : %x, %x\n", a, f1(a), f2(a));
}

int main() {
  puts("### Question 2");
  uint16_t x = 0xA8F1;
  uint16_t y = 0x17DF;
  uint16_t z = 0xCDB8;
  test1(x & y);
  test1(x | y);
  test1(x | (y & z));
  test1(~x | ~y);
  test1(x & !y);
  test1(x & (!y | ~z));
  putchar('\n');
  test1(x && y);
  test1(x || y);
  test1(x || (y && y));
  test1(!x || !y);
  test1(x && ~y);
  test1((~(x & z) | x) & y);
  puts("");

  puts("### Question 3");
  f(-2147483647 - 1 == 2147483648U);
  f(-2147483647 - 1U < 2147483647);
  f(-2147483647 - 1U < -2147483647);
  f(2147483647U > -2147483647 - 1);
  f(2147483647 > (int)2147483648U);
  f(-1 < 0U);
  puts("");

  puts("### Question 4");
  test2(0xdeadbeef);
  test2(0xbaddcafe);
  test2(0x0d15ea5e);
  test2(0xfee1dead);
  puts("");

  return 0;
}
