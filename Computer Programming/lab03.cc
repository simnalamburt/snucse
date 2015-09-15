#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

string s = " = ";

int64_t foo(int64_t num) {
  if (num < 0) { throw num; }
  if (num < 10) {
    s = to_string(num) + s;
    return num;
  }

  s = " + " + to_string(num % 10) + s;

  return num % 10 + foo(num / 10);
}

int main() {
  cout << "Enter a number: " << flush;
  int64_t input;
  cin >> input;

  try {
    int64_t ret = foo(input);
    cout << s << ret << endl;
  } catch (int64_t e) {
    cerr << "Invalid input : " << e << endl;
  }

  return 0;
}
