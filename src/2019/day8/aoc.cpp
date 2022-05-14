#include "aoc.h"
#include <algorithm>

namespace aoc2019 {

struct digits {
  int chars[10] = {0};
};

static void count_digit(const char* p1, const char* p2, digits* p) {
  while (p1 < p2) {
    p->chars[*p1 - '0'] += 1;
    p1++;
  }
}

std::pair<int, int> day8(line_view file) {
  digits ds[100];
  int x = 6 * 25;
  for (int i = 0; i < 100; i++) {
    const char* p1 = file.line + i * x;
    const char* p2 = file.line + (i + 1) * x;
    count_digit(p1, p2, &ds[i]);
  }

  struct ct {
    int zeros = 0;
    int times = 0;
  } cs[100];

  for (int i = 0; i < 100; i++) {
    cs[i].zeros = ds[i].chars[0];
    cs[i].times = ds[i].chars[1] * ds[i].chars[2];
    // for (int j : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    //   printf("%d ", ds[i].chars[j]);
    // }
    // printf("\n");
  }

  std::sort(cs, cs + 100, [](ct c1, ct c2) { return c1.zeros < c2.zeros; });
  return {cs[0].times, 0};
}
} // namespace aoc2019
