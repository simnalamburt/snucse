int ncopy(int *src, int *dst, int len) {
  int count = 0;
  int val;
  while (len > 0) {
    // Loop 0
    val = *src;
    *dst = val;
    if (val > 0) { ++count; }
    ++src;
    ++dst;
    --len;

    if (len <= 0) { break; }

    // Loop 1
    val = *src;
    *dst = val;
    if (val > 0) { ++count; }
    ++src;
    ++dst;
    --len;

    if (len <= 0) { break; }

    // Loop 2
    val = *src;
    *dst = val;
    if (val > 0) { ++count; }
    ++src;
    ++dst;
    --len;

    if (len <= 0) { break; }

    // Loop 3
    val = *src;
    *dst = val;
    if (val > 0) { ++count; }
    ++src;
    ++dst;
    --len;

    if (len <= 0) { break; }

    // Loop 4
    val = *src;
    *dst = val;
    if (val > 0) { ++count; }
    ++src;
    ++dst;
    --len;

    if (len <= 0) { break; }

    // Loop 5
    val = *src;
    *dst = val;
    if (val > 0) { ++count; }
    ++src;
    ++dst;
    --len;

    if (len <= 0) { break; }

    // Loop 6
    val = *src;
    *dst = val;
    if (val > 0) { ++count; }
    ++src;
    ++dst;
    --len;

    if (len <= 0) { break; }

    // Loop 7
    val = *src;
    *dst = val;
    if (val > 0) { ++count; }
    ++src;
    ++dst;
    --len;
  }
  return count;
}
