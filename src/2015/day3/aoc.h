#pragma once

#include "common.h"

namespace aoc2015 {

enum class dir { up, down, left, right };

struct house {
  int x;
  int y;

  bool operator<(const house& h) const noexcept { return x < h.x ? true : (x > h.x ? false : y < h.y); }
};

house move_day3(house, dir);
std::pair<size_t, size_t> day3(line_view);

} // namespace aoc2015
