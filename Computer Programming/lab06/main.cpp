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

  // [(100, 'a'), (50, 'b'), ... ]
  array<entry, 256> freq = {};

  // 배열 초기화
  char ch = 0;
  for (auto& entry: freq) {
    entry.first = 0;
    entry.second = ch++;
  }
  // [(0, 'a'), (0, 'b'), ... ]

  // 입력에서 읽어서 배열에 넣음
  while (true) {
    char ch = input.get();
    if (input.eof()) { break; }
    freq[ch].first += 1;
  }
  input.close();

  // 빈도순으로 정렬함
  sort(freq.begin(), freq.end(), [](entry left, entry right) {
    return left.first > right.first;
  });

  // 출력파일 열기
  ofstream output(argv[2]);
  if (!output.is_open()) {
    cerr << "Unable to open file to write" << endl;
    return 1;
  }

  // 배열 순회하면서 출력
  for (auto entry : freq) {
    size_t count = entry.first;
    char ch = entry.second;
    // 0회일경우, 스킵
    if (count != 0) {
      output << ch << "(value : " << size_t(ch) << "): " << count << endl;
    }
    ++ch;
  }
  output.close();
  return 0;
}
