int ncopy(int *src, int *dst, int len) {
  int count = 0;
  while (len > 0) {
    int val = *src++;
    *dst++ = val;
    if (val > 0) { ++count; }
    --len;
  }
  return count;
}
