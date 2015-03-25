#include <vector>
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace std::chrono;

struct unit { float a, b; };

int main(int argc, char *argv[]) {
  size_t num = argc < 2 ? 512 * 1024 * 1204 : atol(argv[1]);

  float x = 1.1;
  auto begin = high_resolution_clock::now();
  for (size_t i = 0; i < num; ++i) {
    // Fused multiply–add
    x = x*0.95 + 10;
  }
  auto end = high_resolution_clock::now();

  cout << duration_cast<nanoseconds>(end - begin).count() << "ns (" << x << ')' << endl;
  return 0;
}
