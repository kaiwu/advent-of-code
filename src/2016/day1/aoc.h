#pragma once
#include "common.h"
#include <algorithm>
#include <math.h>
#include <set>
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

  bool operator<(const position& p) const noexcept { return x < p.x ? true : (x > p.x ? false : y < p.y); }
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

  std::vector<position> line(position p1, position p2) const noexcept {
    std::vector<position> ps;
    auto copyx = [&p1, &p2, &ps](int x) {
      if (x > 0) {
        for (int i = p1.x; i < p2.x; i++) {
          ps.push_back({p2.b, i, p1.y});
        }
      }
      if (x < 0) {
        for (int i = p1.x; i > p2.x; i--) {
          ps.push_back({p2.b, i, p1.y});
        }
      }
    };
    auto copyy = [&p1, &p2, &ps](int y) {
      if (y > 0) {
        for (int i = p1.y; i < p2.y; i++) {
          ps.push_back({p2.b, p1.x, i});
        }
      }
      if (y < 0) {
        for (int i = p1.y; i > p2.y; i--) {
          ps.push_back({p2.b, p1.x, i});
        }
      }
    };
    copyx(p2.x - p1.x);
    copyy(p2.y - p1.y);
    return ps;
  }

  void cross(position p1, position p2, position* first, bool* found) const noexcept {
    static std::set<position> ps = {};
    if (!(*found)) {
      auto v = line(p1, p2);
      for (size_t i = 0; i < v.size(); i++) {
        // printf("%d %d %d\n", int(v[i].b), v[i].x, v[i].y);
        auto p = ps.insert(v[i]);
        if (!p.second) {
          *found = true;
          *first = *p.first;
          return;
        }
      }
    }
  }

  position move(const std::vector<instruction>& is, position* first, bool* found) const noexcept {
    position next = *this;
    std::for_each(is.begin(), is.end(), [&next, first, found, this](const instruction& i) {
      position prev = next;
      next = next.move(i);
      cross(prev, next, first, found);
    });
    return next;
  }
};

std::pair<int, int> day1(line_view);

} // namespace aoc2016
