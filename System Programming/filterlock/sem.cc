#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include <unistd.h>

using namespace std;

static int var = 0;

int main(int argc, char *argv[]) {
  size_t n = 8;

  int opt;
  while((opt = getopt(argc, argv, "n:")) != -1) {
    n = atoi(optarg);
  }

  cout << "Calculating with " << n << " threads... " << flush;

  mutex mutex;
  auto threads = vector<thread>();
  for (size_t i = 0; i < n; ++i) {
    threads.emplace_back([&](){
      for (size_t _ = 0; _ < 10000000/n; ++_) {
        mutex.lock();
        var += 1;
        mutex.unlock();
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  cout << "Done!" << endl;
  cout << "var : " << var << endl;
  return 0;
}
