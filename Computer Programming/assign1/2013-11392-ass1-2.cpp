#include <iostream>
#include <string>
#include <cassert>

using namespace std;

string getline() {
  string line;
  ::std::getline(cin, line);
  return line;
}

void numerify(string& input) {
  string::iterator i = input.begin();
  string::const_iterator end = input.cend();

  for (; i != end; ++i) {
    uint8_t ch = *i;

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

void stringify(string& input) {
  string::iterator i = input.begin();
  string::const_iterator end = input.cend();

  for (; i != end; ++i) {
    uint8_t ch = *i;

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

int main() {
  while (true) {
    bool encrypt;
    while (true) {
      try {
        cout << "Encrypt (1) Decrypt (2) : " << flush;
        int mode = stoi(getline());
        if (mode != 1 and mode != 2) { throw out_of_range("Please choose between '1' and '2'"); }
        assert(mode == 1 or mode == 2);
        encrypt = mode == 1;
        break;
      } catch(invalid_argument) {
        if (cin.eof()) { cout << endl; return 0; }
        cout << "\n\e[33mPlease choose between '1' and '2'\e[0m" << endl;
      } catch(out_of_range e) {
        cout << "\n\e[33m" << e.what() << "\e[0m" << endl;
      }
    }


    string line;
    while (true) {
      try {
        cout << "Enter string :" << endl;
        line = getline();
        numerify(line);
        break;
      } catch(out_of_range e) {
        cout << "\n\e[33m" << e.what() <<"\e[0m" << endl;
      }
    }


    int64_t key;
    while (true) {
      try {
        cout << "Enter key value : " << flush;
        key = stoll(getline());
        break;
      } catch(invalid_argument e) {
        if (cin.eof()) { cout << endl; return 0; }
        cout << "\n\e[33mPlease type integer as a key\e[0m" << endl;
      }
    }


    string::const_iterator end = line.cend();
    for (string::iterator i = line.begin(); i != end; ++i) {
      uint8_t num = *i;

      int64_t after = (encrypt ? num + key : num - key) % 61ll;
      if (after < 0) { after += 61ll; }
      assert(0 <= after && after < 61);

      *i = after;
    }


    stringify(line);
    cout << line << "\n\n\n" << flush;
  }

  return 0;
}
