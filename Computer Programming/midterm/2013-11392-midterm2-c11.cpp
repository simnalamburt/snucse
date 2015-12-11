#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>

using namespace std;

void panic(const char* msg) {
  cerr << msg << endl;
  exit(1);
}

template <typename Func>
void foreach_word(istream &ifs, Func func) {
  string line, word;
  stringstream iss;

  while (getline(ifs, line, '.')) {
    iss << line;
    while (getline(iss, word, ' ')) {
      func(word);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) { panic("Wrong argument"); }

  unordered_map<string, size_t> counter;

  // 입력 받아와서 counter에 저장
  {
    ifstream input { argv[1] };
    if (not input.is_open()) { panic("No such file"); }

    foreach_word(input, [&](const string &word) {
      counter[word] += 1;
    });
  }

  // unordered_map<K, V> -> vector<pair<K, V>> 변환
  using entity = pair<string, size_t>;
  vector<entity> sorted;
  for (auto &&entity : counter) { sorted.emplace_back(entity); }

  // 정렬
  sort(sorted.begin(), sorted.end(), [](const entity &left, const entity &right) {
    if (left.second != right.second) { return left.second > right.second; }
    return left.first < right.first;
  });

  // 출력
  for (const auto &entity : sorted) {
    cout << entity.first << ": " << entity.second << endl;
  }

  return 0;
}
