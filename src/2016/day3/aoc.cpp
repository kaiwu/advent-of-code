#include "aoc.h"

namespace aoc2016 {

void get_number(const char** pp, int* d) {
  const char* p = *pp;
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *pp = p;
}

bool is_triangle(line_view lv) {
  const char* p = lv.line;
  int is[3] = {0};
  size_t i{0};
  while (p < lv.line + lv.length) {
    if (*p >= '0' && *p <= '9') {
      get_number(&p, &is[i++]);
    }
    p++;
  }
  auto b1 = is[0] + is[1] > is[2];
  auto b2 = is[0] + is[2] > is[1];
  auto b3 = is[1] + is[2] > is[0];
  return b1 && b2 && b3;
}

int day3(line_view file) {
  int total{0};
  per_line(file, [&total](line_view lv) {
    total += int(is_triangle(lv));
    return true;
  });
  return total;
}

} // namespace aoc2016
