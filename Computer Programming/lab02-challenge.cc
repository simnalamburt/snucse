#include <iostream>
#include <vector>

using namespace std;

template <typename T>
bool is_prime(T input) {
  if (input < 2) { return false; }

  for (T i = 2; i*i <= input; ++i) {
    if (input % i == 0) { return false; }
  }

  return true;
}

int main() {
  long f0 = 0, f1 = 1;
  vector<long> fibo = {f0, f1};

  constexpr int limit = 45;
  fibo.reserve(limit);
  for (int i = 2; i < limit; ++i) {
    auto f = f0 + f1;
    fibo.push_back(f);
    f0 = f1;
    f1 = f;
  }

  // 수열 완성됨

  for (auto i : fibo) {
    if (!is_prime(i)) { continue; }

    cout << i << ", " << flush;
  }
  cout << "\b\b " << endl;
}
