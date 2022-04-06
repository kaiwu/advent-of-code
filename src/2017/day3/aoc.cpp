#include "aoc.h"
#include <math.h>

namespace aoc2017 {

std::pair<int, int> circle(int t) {
  int i = 1;
  int j = 0;
  while ((i * i) < t) {
    i += 2;
    j += 1;
  }
  return {j, i};
}

void middles(int i, int m[]) {
  int x = i * i;
  for (int a : {0, 1, 2, 3}) {
    int n = x - i + 1;
    m[a] = (n + x) / 2;
    x = n;
  }
}

int closest(int t, int m[]) {
  int min{INT32_MAX};
  for (int a : {0, 1, 2, 3}) {
    int d = std::abs(t - m[a]);
    if (d < min) {
      min = d;
    }
  }
  return min;
}

int day3(int target) {
  auto p = circle(target);
  int ms[4] = {0};
  middles(p.second, ms);
  // printf("%d -> %d %d %d %d\n", target, ms[0], ms[1], ms[2], ms[3]);
  int d = closest(target, ms);
  return d + p.first;
}

int day3part2(int target) {
  spiral_grid grid{9};
  return grid.fill_until(target);
}

} // namespace aoc2017
