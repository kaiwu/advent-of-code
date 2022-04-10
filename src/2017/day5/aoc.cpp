#include "aoc.h"
#include <vector>

namespace aoc2017 {

int get_number(line_view lv) {
  const char* p = lv.line;
  int sign = 1;
  if (*p == '-') {
    sign = -1;
    p++;
  }
  int d{0};
  while (*p >= '0' && *p <= '9') {
    d = d * 10 + *p - '0';
    p++;
  }
  return d * sign;
}

void follow(int i, std::vector<int>& ins, int* steps) {
  // printf("%d\n", ins[i]);
  int x = ins[i];
  int n = i + x;
  if (n >= 0 && n < int(ins.size())) {
    // ins[i] += x >= 3 ? -1 : 1; part2
    ins[i] += 1;
    *steps += 1;
    follow(n, ins, steps);
  }
}

int day5(line_view file) {
  std::vector<int> ins;
  per_line(file, [&ins](line_view lv) {
    ins.emplace_back(get_number(lv));
    return true;
  });
  int steps{0};
  follow(0, ins, &steps);
  return steps + 1;
}

} // namespace aoc2017
