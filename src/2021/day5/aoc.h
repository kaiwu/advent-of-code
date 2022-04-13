#pragma once

#include "common.h"

namespace aoc2021 {

struct line {
  struct point {
    int x;
    int y;
  };
  point p1;
  point p2;
};

std::pair<int, int> day5(line_view);
} // namespace aoc2021
