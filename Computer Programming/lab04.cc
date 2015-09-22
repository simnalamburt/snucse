#include <iostream>
#include <utility>

class complex {
  private:
    int real, imag;

  public:
    complex(int real, int imag) : real{real}, imag{imag} {}

    const complex& operator+() const {
      return (*this);
    }

    complex operator-() const {
      return { -real, -imag };
    }

    complex operator+(const complex &right) const {
      return { real + right.real, imag + right.imag };
    }

    complex operator-(const complex &right) const {
      return (*this) + (-right);
    }

    complex operator*(const complex &right) const {
      return {
        real * right.real - imag * right.imag,
        real * right.imag + imag * right.real
      };
      // (a + bi)*(c + di) = a*c - b*d  + i(a*d + b*c)
    }

    void swap(complex &right) {
      using std::swap;

      swap(real, right.real);
      swap(imag, right.imag);
    }

    friend std::ostream& operator<<(std::ostream &, const complex &);
};

std::ostream& operator<<(std::ostream &os, const complex &complex) {
  os << complex.real << " + " << complex.imag << 'i';
  return os;
}

int main() {
  using std::cin;
  using std::cout;
  using std::endl;
  using std::flush;

  int left_real, left_imag, right_real, right_imag;

  cout << "Input the first real number : " << flush;
  cin >> left_real;
  cout << "Input the first imaginary number : " << flush;
  cin >> left_imag;
  cout << "Input the second real number : " << flush;
  cin >> right_real;
  cout << "Input the second imaginary number : " << flush;
  cin >> right_imag;

  complex left { left_real, left_imag };
  complex right { right_real, right_imag };

  cout << "Sum of them : " << left + right << endl;
  cout << "Subtract of them : " << left - right << endl;
  cout << "Multiple of them : " << left * right << endl;

  left.swap(right);
  cout << "-----swap-----" << endl;

  cout << "Sum of them : " << left + right << endl;
  cout << "Subtract of them : " << left - right << endl;
  cout << "Multiple of them : " << left * right << endl;

  return 0;
}
