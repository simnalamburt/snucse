#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

static int var = 0;

int main() {
  const size_t n = 8;

  mutex mutex;

  auto threads = vector<thread>();
  for (size_t i = 0; i < n; ++i) {
    threads.emplace_back([&](){
      for (size_t _ = 0; _ < 1000000/n; ++_) {
        mutex.lock();
        var += 1;
        mutex.unlock();
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  cout << "var : " << var << endl;
  return 0;
}
