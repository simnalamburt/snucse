#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
  while (true) {
    cout << "Enter a number, or 'n' to stop : " << flush;

    string input;
    cin >> input;
    if (input == "n") { return 0; }

    long num;
    try {
      num = stol(input);
    } catch (invalid_argument& e) {
      cout << "\nPlease give me a valid input" << endl;
      continue;
    }

    if (num % 2 == 0) {
      // Even
      for (long y = 0; y < num; ++y) {
        for (long x = 0; x < num; ++x) { cout << '*'; }
        cout << '\n';
      }
    } else {
      // Odd
      for (long y = 0; y < num; ++y) {
        long x = 0;
        for (; x < num - y - 1; ++x) { cout << ' '; }
        for (; x < num; ++x) { cout << '*'; }
        cout << '\n';
      }
    }
    cout << '\n';
  }
}
