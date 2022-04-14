#pragma once

#include "common.h"
#include <math.h>

namespace aoc2021 {

struct line {
  struct point {
    int x;
    int y;

    bool operator<(const point& p) const noexcept { return x < p.x ? true : x > p.x ? false : y < p.y; }
    point move_h(int d) { return {x + d, y}; }
    point move_v(int d) { return {x, y + d}; }
    point move_p(int d) { return {x + d, y + d}; }
    point move_d(int d) { return {x + d, y - d}; }
  };
  point p1;
  point p2;

  bool is_vertical() const noexcept { return p1.x == p2.x; }
  bool is_horizontal() const noexcept { return p1.y == p2.y; }
  bool is_diagonal() const noexcept { return std::abs(p2.x - p1.x) == std::abs(p2.y - p1.y); }

  template <typename F>
  void traverse(F&& f) const noexcept {
    auto next = [this](point x) {
      if (is_vertical()) {
        return x.move_v(1);
      }
      if (is_horizontal()) {
        return x.move_h(1);
      }
      if (is_diagonal()) {
        return p2.y > p1.y ? x.move_p(1) : x.move_d(1);
      }
      return x;
    };
    point p = p1;
    while (p < p2) {
      f(p);
      p = next(p);
    }
    f(p); // p == p2
  }
};

std::pair<int, int> day5(line_view);
} // namespace aoc2021
