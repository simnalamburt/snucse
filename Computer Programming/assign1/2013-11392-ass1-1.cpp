//
// 컴퓨터 프로그래밍, 과제 1번 연습문제 2번.
//
// C++11 문법이 허용되는지 여부를 몰라서 C++03 문법으로 코딩하였음
//

#include <iostream>
#include <cassert>
#include <cstdlib>

typedef unsigned long long ullong;

namespace {
  //
  // 터미널 컬러코드. 좀더 색이 풍부한 화면을 제공한다.
  //
  const char *green  = "\e[32m";
  const char *orange = "\e[33m";
  const char *blue   = "\e[34m";
  const char *reset  = "\e[0m";
}

//
// 유저에게 적절한 안내메세지를 보여주고, 유저가 입력한 정수를 받음.
// 음수일경우 입력을 다시 요청하고, EOF일경우 프로그램을 종료한다.
//
ullong getint(const char *msg) {
  using namespace std;

  while (true) {
    try {
      cout << msg << blue << flush;
      long long input;
      cin >> input;
      if (cin.eof()) { cout << '\n'; exit(0); } // EOF일경우 프로그램 종료
      cout << reset;

      if (input < 0) { throw out_of_range("Input should always be greater or equal to zero"); }
      assert(input >= 0);

      return input;
    } catch(out_of_range e) {
      cout << orange << e.what() << reset << endl;
    }
  }
}

//
// 입력으로 주어진 정수가 십진수로 표현하였을때 총 몇자리 숫자인지 반환
//
size_t digits(ullong input) {
  size_t count = 1;
  while (input >= 10) {
    input /= 10;
    ++count;
  }
  return count;
}

//
// (10**iexp)를 반환하는 헬퍼 함수
//
ullong pow10(size_t iexp) {
  ullong ret = 1;
  while (iexp > 0) {
    ret *= 10;
    --iexp;
  }
  return ret;
}

//
// x가 y의 서브스트링인지 아닌지 검사하는 함수.
//
// x가 y보다 클경우 무조건 false를 반환하고, x가 y와 같을경우 즉시 true를 반환한다.
// x가 십진수로 N자리 숫자일경우, y에서 낮은 N자리와 x가 같은지 틀린지 비교하여,
//   같을경우 true를 반환하고,
//   다를경우 y에서 제일 낮은 자리의 숫자 하나를 빼어 (y/10), 재귀적으로 다시 비교한다.
//
bool substring(ullong x, ullong y) {
  if (x > y) { return false; }
  if (x == y) { return true; }

  ullong mask = pow10(digits(x));

  if (y % mask == x) {
    return true;
  } else {
    return substring(x, y/10);
  }
}

//
// x가 y의 서브시퀀스인지 아닌지 검사하는 함수.
//
// x가 y보다 클경우 무조건 false를 반환하고, x가 y와 같을경우 즉시 true를 반환한다.
// x와 y의 가장 작은 자리의 숫자를 비교하여,
//   같을경우 x와 y의 다음 자리숫자를 다시 재귀적으로 비교하고 (x/10, y/10),
//   다를경우 x는 그대로 두고 y에서 가장 낮은 자리의 숫자를 하나 빼어 (x, y/10), 재귀적으로 다시 비교한다.
//
bool subsequence(ullong x, ullong y) {
  if (x > y) { return false; }
  if (x == y) { return true; }

  int x0 = x % 10;
  int y0 = y % 10;

  if (x0 == y0) {
    return subsequence(x/10, y/10);
  } else {
    return subsequence(x, y/10);
  }
}

//
// 메인함수
//
int main() {
  using namespace std;

  // 프로그램 루프
  while (true) {
    ullong y = getint("Enter Y : ");
    ullong x = getint("Enter X : ");

    // x가 y의 substring일경우, 자명하게 x는 무조건 y의 subsequence이다.
    // 그러므로 먼저 substring인지 여부만 검사하고, 아니었을경우에
    // subsequence인지 검사한다.
    cout << green;
    if (substring(x, y)) {
      cout << "X is substring of Y" << endl;
    } else if (subsequence(x, y)) {
      cout << "X is subsequence of Y" << endl;
    } else {
      cout << "X is neither substring nor subsequence of Y" << endl;
    }
    cout << reset << endl;
  }

  return 0;
}
