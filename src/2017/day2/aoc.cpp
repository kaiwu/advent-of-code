#include "aoc.h"
#include <vector>
#include <climits>

namespace aoc2017 {

int get_number(const char** pp) {
  const char* p = *pp;
  int d{0};
  while (*p >= '0' && *p <= '9') {
    d = d * 10 + *p - '0';
    p++;
  }
  *pp = p;
  return d;
}

int evenly_divisible(int x, int y) {
  int max = std::max(x, y);
  int min = std::min(x, y);
  return max % min == 0 ? max / min : 0;
}

int diffr(size_t i, const std::vector<int>& v) {
  if (i == v.size() - 1) {
    return 0;
  } else {
    for (size_t j = i + 1; j < v.size(); j++) {
      int d = evenly_divisible(v[i], v[j]);
      if (d > 0) {
        return d;
      }
    }
    return diffr(i + 1, v);
  }
}

int diff(line_view lv, std::vector<int>& v) {
  int max{INT_MIN};
  int min{INT_MAX};
  const char* p = lv.line;
  while (p < lv.line + lv.length) {
    if (*p >= '0' && *p <= '9') {
      int d = get_number(&p);
      if (d > max)
        max = d;
      if (d < min)
        min = d;
      v.push_back(d);
    }
    p++;
  }
  return max - min;
}

std::pair<int, int> day2(line_view file) {
  int sum1{0};
  int sum2{0};
  per_line(file, [&sum1, &sum2](line_view lv) {
    std::vector<int> v;
    sum1 += diff(lv, v);
    sum2 += diffr(0, v);
    return true;
  });
  return {sum1, sum2};
}

} // namespace aoc2017
