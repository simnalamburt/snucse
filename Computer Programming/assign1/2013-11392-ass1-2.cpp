//
// 컴퓨터 프로그래밍, 과제 1번 연습문제 2번.
//
// C++11 문법이 허용되는지 여부를 몰라서 C++03 문법으로 코딩하였음
//

#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>

using namespace std;

//
// 유저가 다음 개행문자('\n')를 입력할때까지 쓴 입력을 모두 받음.
// 개행문자는 결과에 포함되지 않음.
//
string getline() {
  string line;
  ::std::getline(cin, line);
  return line;
}

//
// {a~z}, {A~Z}, {1~9} 로 이뤄진 문자열의 각 글자들을 [0, 61) 범위의 숫자로 1:1
// 대응시킨다.
//
// 범위 밖의 입력이 들어올경우, std::out_of_range 예외를 발생시킨다.
//
void numerify(string& input) {
  string::iterator i = input.begin();
  string::const_iterator end = input.end();

  // 이터레이터로 각 글자에 대해 모두 실행함
  for (; i != end; ++i) {
    unsigned char ch = *i;

    if ('a' <= ch && ch <= 'z') {
      ch = ch - 'a';
    } else if ('A' <= ch && ch <= 'Z') {
      ch = ch - 'A' + ('z' - 'a' + 1);
    } else if ('1' <= ch && ch <= '9') {
      ch = ch - '1' + ('z' - 'a' + 1) + ('Z' - 'A' + 1);
    } else {
      throw out_of_range("Input string should consist of {a~z}, {A~Z}, {1~9} (0 is not permitted)");
    }

    // ('9' - '1' + 1) + ('z' - 'a' + 1) + ('Z' - 'A' + 1) == 61

    *i = ch;
  }
}

//
// numerify() 함수의 역함수
//
// 범위 밖의 입력이 들어올경우, std::out_of_range 예외를 발생시킨다.
//
void stringify(string& input) {
  string::iterator i = input.begin();
  string::const_iterator end = input.end();

  for (; i != end; ++i) {
    unsigned char ch = *i;

    if (ch <= 'z' - 'a') {
      ch += 'a';
    } else if (ch <= 'Z' - 'A' + ('z' - 'a' + 1)) {
      ch += 'A' - ('z' - 'a' + 1);
    } else if (ch <= '9' - '1' + ('z' - 'a' + 1) + ('Z' - 'A' + 1)) {
      ch += '1' - ('z' - 'a' + 1) - ('Z' - 'A' + 1);
    } else {
      throw out_of_range("Numerified string should consist of {x | 0 <= x < 61}");
    }

    *i = ch;
  }
}

//
// 프로그램 본체
//
int main() {
  //
  // 터미널 컬러코드
  //
  const char *blue = "\e[34m";
  const char *orange = "\e[33m";
  const char *green = "\e[32m";
  const char *reset = "\e[0m";

  while (true) {
    // Encrypt인지, Decrypt인지 입력받는다.
    // 반복문을 써서, 잘못된 입력이 들어올경우 올바른 입력이 주어질때까지 반복한다
    bool encrypt;
    while (true) {
      try {
        cout << "Encrypt (1), Decrypt (2), Exit (q) : " << blue << flush;
        string line = getline();
        if (line == "q") { return 0; }

        int mode = atoi(line.c_str());
        cout << reset;
        if (mode != 1 and mode != 2) { throw out_of_range("Please choose between '1' and '2'"); }
        assert(mode == 1 or mode == 2);
        encrypt = mode == 1;
        break;
      } catch(invalid_argument) {
        // EOF가 주어질경우 프로그램을 꺼버린다.
        if (cin.eof()) { cout << endl; return 0; }
        cout << orange << "Please choose between '1' and '2'" << reset << endl;
      } catch(out_of_range e) {
        cout << orange << e.what() << reset << endl;
      }
    }

    // 시저 암호를 적용시킬 문자열을 입력받는다.
    // 반복문을 써서, 잘못된 입력이 들어올경우 올바른 입력이 주어질때까지 반복한다
    string line;
    while (true) {
      try {
        cout << "Enter string :" << blue << endl;
        line = getline();
        cout << reset;
        numerify(line);
        break;
      } catch(out_of_range e) {
        cout << orange << e.what() << reset << endl;
      }
    }

    // 키를 입력받는다
    long long key;
    while (true) {
      try {
        cout << "Enter key value : " << blue << flush;
        key = atoi(getline().c_str());
        cout << reset;
        break;
      } catch(invalid_argument e) {
        if (cin.eof()) { cout << endl; return 0; }
        cout << orange << "Please type integer as a key" << reset << endl;
      }
    }

    // 문자열의 각 글자에 대해 시저암호를 계산한다
    string::const_iterator end = line.end();
    for (string::iterator i = line.begin(); i != end; ++i) {
      unsigned char num = *i;

      long long after = (encrypt ? num + key : num - key) % 61ll;
      if (after < 0) { after += 61ll; }
      assert(0 <= after && after < 61);

      *i = after;
    }

    // 숫자로 변환된 문자열을 다시 문자열로 바꾼다
    stringify(line);
    cout << '\n' << green << line << reset << "\n\n\n" << flush;
  }

  return 0;
}
