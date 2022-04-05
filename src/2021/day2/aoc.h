#pragma once

#include "common.h"

namespace aoc2021 {

struct meters {
  int horizontal;
  int depth;

  int get_number(const char* p) {
    int d{0};
    while (*p >= '0' && *p <= '9') {
      d = d * 10 + *p - '0';
      p++;
    }
    return d;
  }

  void apply(line_view lv) {
    const char* p = lv.contains(" ");
    int d = get_number(p + 1);
    if (line_view{lv.line, p} == line_view{"forward"}) {
      horizontal += d;
    }
    if (line_view{lv.line, p} == line_view{"down"}) {
      depth += d;
    }
    if (line_view{lv.line, p} == line_view{"up"}) {
      depth -= d;
    }
  }

  void apply(line_view lv, int* aim) {
    const char* p = lv.contains(" ");
    int d = get_number(p + 1);
    if (line_view{lv.line, p} == line_view{"forward"}) {
      horizontal += d;
      depth += *aim * d;
    }
    if (line_view{lv.line, p} == line_view{"down"}) {
      *aim += d;
    }
    if (line_view{lv.line, p} == line_view{"up"}) {
      *aim -= d;
    }
  }
};

std::pair<int, int> day2(line_view);

} // namespace aoc2021
