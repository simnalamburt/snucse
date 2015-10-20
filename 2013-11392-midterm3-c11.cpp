#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

[[ noreturn ]]
void panic(const char* msg) {
  cerr << msg << endl;
  exit(1);
}

class School {
  class Class {
    size_t count = 0;
  public:
    static constexpr size_t MAX = 50;
    static constexpr size_t MIN = 25;

    void in(size_t &num) {
      size_t capacity = MAX - count;

      if (capacity >= num) {
        // 넣고 남거나, 딱 맞음
        count += num;
        num = 0;
      } else {
        // 다 못넣음
        count = MAX;
        num -= capacity;
      }
    }

    void out(size_t &num) {
      if (count >= num) {
        // 빼고 남거나, 딱 맞음
        count -= num;
        num = 0;
      } else {
        // 모두 빼고도 더 빼야함
        num -= count;
        count = 0;
      }
    }

    size_t get() const { return count; }
    void force_set(size_t num) { count = num; }
  };

  vector<Class> classes;
  mutable ofstream output;

public:
  explicit School(const char *filename) : output(filename) {
    if (not output.is_open()) { panic("Could not write to output file"); }
  }

  void in(size_t num) {
    in_without_otherjob(num);

    if (classes.back().get() < Class::MIN) { spread(); }
    print();
  }

  void in_without_otherjob(size_t num) {
    for (auto &room : classes) {
      room.in(num);
      if (num == 0) { break; }
    }

    // New rooms
    while (num > 0) {
      Class room;
      room.in(num);
      classes.emplace_back(room);
    }
  }

  void out(size_t num) {
    const auto end = classes.crend();
    for (auto it = classes.rbegin(); it != end; ++it) {
      auto &room = *it;
      room.out(num);
      if (num == 0) { break; }
    }

    // Remove empty rooms
    while (true) {
      const auto &lastroom = classes.back();
      if (lastroom.get() != 0) { break; }
      classes.pop_back();
    }

    if (classes.back().get() < Class::MIN) {
      spread();

      // Once more
      auto last = classes.back().get();
      if (last < Class::MIN) {
        classes.pop_back();
        in_without_otherjob(last);
      }
    }

    print();
  }

private:
  void print() const {
    ostringstream buffer;
    for (const auto &room : classes) {
      buffer << room.get() << ' ';
    }
    auto msg = buffer.str();
    if (not msg.empty()) { msg.pop_back(); }
    output << msg << endl;
  }

  void spread() {
    size_t total = 0;
    for (const auto &room : classes) { total += room.get(); }

    size_t count = classes.size();
    size_t average = total / count;
    size_t residue = total % count;

    for (auto &room : classes) { room.force_set(average); }

    for (auto &room : classes) {
      if (residue == 0) { return; }
      room.force_set(average + 1);
      residue -= 1;
    }
  }
};

int main(int argc, char *argv[]) {
  if (argc != 3) { panic("Wrong argument"); }

  School school { argv[2] };

  // 입력파일 읽음
  {
    ifstream input { argv[1] };
    if (not input.is_open()) { panic("No such input file"); }

    while (true) {
      string command;
      size_t number;
      input >> command >> number;
      if (input.eof()) { break; }

      if (command == "in") { school.in(number); }
      else if (command == "out") { school.out(number); }
      else { panic("Bad input"); }
    }
  }

  return 0;
}
