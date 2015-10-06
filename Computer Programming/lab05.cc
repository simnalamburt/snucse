#include <iostream>
#include <array>

using namespace std;

int main() {
  {
    cout << "## 1" << endl;
    cout << "Enter ten numbers: " << flush;
    constexpr size_t count = 10;
    int num[count];
    for (int& i : num) { cin >> i; }

    for (int i : num) { cout << i << ", "; }
    cout << "\b\b  ->  ";

    for (size_t i = 0; i < count; ++i) {
      for (size_t j = i; j < count; ++j) {
        int &a = num[i], &b = num[j];
        if (a > b) { swap(a, b); }
      }
    }

    for (int i : num) { cout << i << ", "; }
    cout << "\b\b " << endl;
    cout << endl;
  }

  {
    cout << "## 2" << endl;
    cout << "Enter nine numbers: " << flush;

    constexpr size_t count = 9;
    int num[count], sorted[count];
    for (size_t i = 0; i < count; ++i) {
      int t;
      cin >> t;
      num[i] = sorted[i] = t;
    }

    sort(sorted, sorted + count);

    cout << "Input:\tSorted\t" << endl;
    for (int y = 0; y < 3; ++y) {
      for (int x = 0; x < 3; ++x) { cout << num[x + y*3] << ' '; }
      cout << "\b\t";
      for (int x = 0; x < 3; ++x) { cout << sorted[x + y*3] << ' '; }
      cout << '\n';
    }
  }
}

bool prob3()
