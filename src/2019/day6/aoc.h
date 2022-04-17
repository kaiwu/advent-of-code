#pragma once
#include "common.h"
#include <set>

namespace aoc2019 {

struct star {
  line_view name;
  std::set<star*> orbits = {};

  star(line_view lv): name(lv) {}
};

int day6(line_view);

} // namespace aoc2019
