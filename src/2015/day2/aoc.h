#pragma once

#include "common.h"

namespace aoc2015 {

struct box {
  int l;
  int w;
  int h;
};

box parse_day2(line_view lv);
int min_day2(box);
int surface(box);
std::pair<int, int> day2(line_view);

} // namespace aoc2015
