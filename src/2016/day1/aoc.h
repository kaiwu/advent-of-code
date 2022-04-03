#pragma once
#include "common.h"
#include <algorithm>
#include <math.h>
#include <vector>

namespace aoc2016 {

struct instruction {
  enum {
    left = 0,
    right,
  } direction;
  int distance;
};

struct position {
  enum bearing {
    north = 0,
    east,
    south,
    west,
  } b;

  int x;
  int y;

  int blocks(position p) const noexcept { return abs(p.x - x) + abs(p.y - y); }

  position move(instruction i) const noexcept {
    auto putx = [this](int d) { return x; };
    auto puty = [this](int d) { return y; };
    auto addx = [this](int d) { return x + d; };
    auto subx = [this](int d) { return x - d; };
    auto addy = [this](int d) { return y + d; };
    auto suby = [this](int d) { return y - d; };

    struct {
      bearing bs[2];
      std::function<int(int)> lr[4];
    } moves[] = {
        {{west, east}, {subx, addx, puty, puty}},
        {{north, south}, {putx, putx, addy, suby}},
        {{east, west}, {addx, subx, puty, puty}},
        {{south, north}, {putx, putx, suby, addy}},
    };
    position next;
    next.b = moves[int(b)].bs[int(i.direction)];
    next.x = moves[int(b)].lr[int(i.direction)](i.distance);
    next.y = moves[int(b)].lr[int(i.direction) + 2](i.distance);

    return next;
  }

  position move(const std::vector<instruction>& is) const noexcept {
    position next = *this;
    std::for_each(is.begin(), is.end(), [&next](const instruction& i) { next = next.move(i); });
    return next;
  }
};

std::vector<instruction> parse_day1(line_view);

} // namespace aoc2016
