#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

string output;

void print(int number, int base) {
  if (number == 0) { return; }

  int digit = number % base;
  char ch;
  if (0 <= digit && digit < 10) {
    ch = '0' + digit;
  } else if (10 <= digit && digit < 36) {
    ch = 'A' + (digit - 10);
  } else if (36 <= digit) {
    cerr << "Wrong input" << endl;
    exit(1);
  }
  output = ch + output;

  print(number/base, base);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Wrong input" << endl;
    return 1;
  }

  int number = atoi(argv[1]);
  int base = atoi(argv[2]);
  print(number, base);

  cout << output << endl;
  return 0;
}
