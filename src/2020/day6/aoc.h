#pragma once
#include "common.h"

namespace aoc2020 {

struct question_group {
  line_view people;
  int count[26] = {0};

  int summary() const noexcept {
    int total{0};
    for (int x : count) {
      total += int(x > 0);
    }
    return total;
  }

  question_group(line_view lv) : people(lv) {
    const char* p = lv.line;
    while (p < lv.line + lv.length) {
      if (*p >= 'a' && *p <= 'z') {
        count[*p - 'a'] += 1;
      }
      p++;
    }
  }
};

int day6(line_view);

} // namespace aoc2020
