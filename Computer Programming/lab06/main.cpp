#include <iostream>
#include <fstream>
#include <array>

using namespace std;

using entry = pair<size_t, char>;

int main(int argc, char **argv) {
  if (argc != 3) {
    cerr << "Need argument readfile and outputfile" << endl;
    return 1;
  }

  ifstream input(argv[1]);
  if (!input.is_open()) {
    cerr << "Unable to open file to read" << endl;
    return 1;
  }

  array<entry, 256> freq = {};

  char ch = 0;
  for (auto& entry: freq) {
    entry.first = 0;
    entry.second = ch++;
  }

  while (true) {
    char ch = input.get();
    if (input.eof()) { break; }
    freq[ch].first += 1;
  }
  input.close();

  sort(freq.begin(), freq.end(), [](entry left, entry right) {
    return left.first > right.first;
  });

  ofstream output(argv[2]);
  if (!output.is_open()) {
    cerr << "Unable to open file to write" << endl;
    return 1;
  }

  for (auto entry : freq) {
    size_t count = entry.first;
    char ch = entry.second;
    if (count != 0) {
      output << ch << "(value : " << size_t(ch) << "): " << count << endl;
    }
    ++ch;
  }
  output.close();
  return 0;
}
