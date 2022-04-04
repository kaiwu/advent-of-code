#include "aoc.h"

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

int diff(line_view lv) {
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
    }
    p++;
  }
  return max - min;
}

int day2(line_view file) {
  int sum{0};
  per_line(file, [&sum](line_view lv) {
    sum += diff(lv);
    return true;
  });
  return sum;
}

} // namespace aoc2017
