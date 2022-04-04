#include "aoc.h"
#include <set>

namespace aoc2018 {
int parse_day1(line_view lv) {
  const char* p = lv.line;
  int sign = *p++ == '+' ? 1 : -1;
  int s{0};
  while (*p >= '0' && *p <= '9') {
    s = s * 10 + *p - '0';
    p++;
  }
  return sign * s;
}

int day1(line_view file) {
  int sum{0};

  per_line(file, [&sum](line_view lv) {
    sum += parse_day1(lv);
    return true;
  });
  return sum;
}

int day1part2(line_view file) {
  std::set<int> frequencies;

  int f{0};
  bool found{false};
  while (!found) {
    per_line(file, [&f, &frequencies, &found](line_view lv) {
      f += parse_day1(lv);
      // printf("%d\n", f);
      auto p = frequencies.insert(f);
      found = !p.second;
      return p.second;
    });
  }
  return f;
}

} // namespace aoc2018
