#include "aoc.h"

namespace aoc2019 {

int parse_day1(line_view lv) {
  int d{0};
  const char* p = lv.line;
  while (*p >= '0' && *p <= '9') {
    d = d * 10 + *p - '0';
    p++;
  }
  return d;
}

int day1(line_view file) {
  int fuel{0};
  auto cal = [](int m) -> int { return m / 3 - 2; };
  per_line(file, [&fuel, &cal](line_view lv) {
    fuel += cal(parse_day1(lv));
    return true;
  });

  return fuel;
}

void add_fuel(int base, int* total) {
  if (base > 0) {
    // printf("%d\n", base);
    *total += base;
    add_fuel(base / 3 - 2, total);
  }
}

int day1part2(line_view file) {
  int fuel{0};
  per_line(file, [&fuel](line_view lv) {
    int total{0};
    int base = parse_day1(lv);
    add_fuel(base / 3 - 2, &total);
    fuel += total;
    return true;
  });

  return fuel;
}

} // namespace aoc2019
