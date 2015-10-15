int fun(int from, int to) {
  int result;

  volatile int TRUE = 1;
  do {
    do {
      if (TRUE) {
        result = from/4 > to*2;
      }
    } while(!TRUE);
  } while(!TRUE);

  return result;
}

int main(int argc, char* argv[]) {
  int result = fun(1, 10);
  return 0;
}
