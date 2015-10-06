#include <iostream>

class bucket {
  static constexpr size_t max_size = 10;
  size_t cook;

public:
  bucket() : cook(0) { }

  size_t add_cook(size_t count) {
    cook += count;
    if (cook > max_size) {
      size_t ret = cook - max_size;
      cook = max_size;
      return ret;
    } else {
      return 0;
    }
  }

  size_t delete_cook(size_t count) {
    if (cook >= count) {
      cook -= count;
      return 0;
    } else {
      size_t ret = count - cook;
      cook = 0;
      return ret;
    }
  }

  size_t get_cook_num() { return cook; }
};

class cookManager {
  size_t buck_size;
  bucket *bucks;

  void realloc_buckets(size_t new_size) {
    size_t after_size = buck_size + new_size;

    bucket *temp = new bucket[after_size];
    for (size_t i = 0; i < buck_size; ++i) { temp[i] = bucks[i]; }

    delete[] bucks;
    bucks = temp;

    buck_size = after_size;
  }

public:
  cookManager() : buck_size(1), bucks(new bucket[buck_size]) { }
  ~cookManager() { delete[] bucks; }

  void add_cookies(size_t count) {
    for (size_t i = 0;; ++i) {
      if (i >= buck_size) {
        realloc_buckets(buck_size);
      }

      count = bucks[i].add_cook(count);
      if (count == 0) { break; }
    }
  }

  void delete_cookies(size_t count) {
    for (size_t i = buck_size - 1; i != size_t(-1); --i) {
      count = bucks[i].delete_cook(count);
      if (count == 0) { break; }
    }
  }

  void print() {
    using namespace std;

    cout << "Bucket Status\n"
      "----------------\n";
    for (size_t i = 0; i < buck_size; ++i) {
      size_t num = bucks[i].get_cook_num();
      if (num == 0) { break; }
      cout << i << (
          i % 10 == 1 ? "st" :
          i % 10 == 2 ? "nd" : "th"
          ) << " bucket : " << num << "cookies" << endl;
    }
  }
};

int main() {
  using namespace std;

  cookManager mgr;
  int input;

  cout << "There is a cookie bucket." << endl;

  while (true) {
    cout << "How many cookies are coming? : " << flush;
    cin >> input;
    mgr.add_cookies(input);

    cout << "How many cookies are eaten? : " << flush;
    cin >> input;
    mgr.delete_cookies(input);

    mgr.print();

    cout << "Keep going? (type 'y' to continue) : " << flush;
    char cont;
    cin >> cont;
    if (cont != 'y') { return 0; }
  }
}
