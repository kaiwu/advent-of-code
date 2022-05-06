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

int crab_move(int x, int y) {
  int b = std::abs(x - y);
  return b * (b + 1) / 2;
}

std::pair<int, int> fuel(int a, const std::map<int, int>& is) {
  int t0{0};
  int t1{0};
  for (auto& kv : is) {
    if (kv.first != a) {
      t0 += std::abs(a - kv.first) * kv.second;
      t1 += crab_move(a, kv.first) * kv.second;
    }
  }
  return {t0, t1};
}

std::pair<int, int> day7(line_view file) {
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

  int m1{INT32_MAX};
  int m2{INT32_MAX};
  for (int i = mi; i <= mx; i++) {
    auto p = fuel(i, is);
    // printf("%d -> (%d, %d)\n", i, p.first, p.second);
    if (p.first < m1) {
      m1 = p.first;
    }
    if (p.second < m2) {
      m2 = p.second;
    }
  }
  return {m1, m2};
}

} // namespace aoc2021
