#include "aoc.h"
#include <map>

namespace aoc2021 {
static void get_number(const char** pp, int* d) {
  const char* p = *pp;
  *d = 0;
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *pp = p;
}

int fuel(int a, const std::map<int, int>& is) {
  int total{0};
  for (auto& kv : is) {
    if (kv.first != a) {
      total += std::abs(a - kv.first) * kv.second;
    }
  }
  return total;
}

int day7(line_view file) {
  std::map<int, int> is;
  const char* p1 = file.line;
  const char* p2 = p1 + file.length;
  int mi{INT32_MAX};
  int mx{INT32_MIN};
  while (p1 < p2) {
    if (*p1 >= '0' && *p1 <= '9') {
      int d{0};
      get_number(&p1, &d);
      mi = std::min(mi, d);
      mx = std::max(mx, d);
      is[d] += 1;
    }
    p1++;
  }

  int min{INT32_MAX};
  for (int i = mi; i <= mx; i++) {
    int f = fuel(i, is);
    // printf("%d -> %d\n", i, f);
    if (f < min) {
      min = f;
    }
  }

  return min;
}

} // namespace aoc2021
