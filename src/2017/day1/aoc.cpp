#include "aoc.h"

namespace aoc2017 {

int day1(line_view lv) {
  int sum{0};
  const char* p1 = lv.line;
  const char* p2 = p1 + 1;
  while (*p2 >= '0' && *p2 <= '9') {
    if (*p1 == *p2) {
      sum += *p1 - '0';
    }
    p1++;
    p2++;
  }
  if (*p1 == *lv.line) {
    sum += *p1 - '0';
  }
  return sum;
}

int day1part2(line_view lv) {
  int sum{0};
  size_t size = lv.length % 2 == 0 ? lv.length : lv.length - 1;
  const char* p1 = lv.line;
  const char* p = lv.line + size / 2;
  while (*p1 >= '0' && *p1 <= '9') {
    const char* p2 = p1 < p ? (p + (p1 - lv.line)) : (lv.line + (p1 - p));
    if (*p1 == *p2) {
      sum += *p1 - '0';
    }
    p1++;
  }
  return sum;
}

} // namespace aoc2017
