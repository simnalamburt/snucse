int copy_block(int *src, int *dest, int len)
{
  int result = 0;
  while (len > 0) {
    int val = *src++;
    *dest++ = val;
    result ^= val;
    len--;
  }
  return result;
}
