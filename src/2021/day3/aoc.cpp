#include "aoc.h"

namespace aoc2021 {

int decimal(const char* p) {
  int d{0};
  while (*p == '0' || *p == '1') {
    d = 2 * d + *p - '0';
    p++;
  }
  return d;
}

int day3(line_view file) {
  char gamma[13] = {0};
  char epsilon[13] = {0};

  int is[12] = {0};
  int total{0};
  per_line(file, [&is, &total](line_view lv) {
    for (int i = 0; i < 12; i++) {
      if (*(lv.line + i) == '1') {
        is[i] += 1;
      }
    }
    total += 1;
    return true;
  });

  for (int i = 0; i < 12; i++) {
    if (is[i] > total / 2) {
      gamma[i] = '1';
      epsilon[i] = '0';
    } else {
      gamma[i] = '0';
      epsilon[i] = '1';
    }
  }

  // printf("%s\n", gamma);
  // printf("%s\n", epsilon);

  return decimal(gamma) * decimal(epsilon);
}

} // namespace aoc2021
