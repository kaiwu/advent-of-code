#pragma once
#include "common.h"
#include <algorithm>
#include <vector>

namespace aoc2017 {

struct spiral_grid {
  int dim;
  std::vector<int> cells;

  struct pos {
    int x;
    int y;

    bool operator>(pos other) const noexcept { return x > other.x && y == other.y; }
  };

  int get(pos p) const noexcept {
    int x = dim / 2;
    int y = dim / 2;
    return (p.y + y) * dim + p.x + x;
  }

  int value(pos p) const noexcept {
    if (std::abs(p.x) > dim / 2 || std::abs(p.y) > dim / 2) {
      return 0;
    }
    return cells[get(p)];
  }

  // 3, 5, 7, 9
  spiral_grid(int d) : dim(d), cells(dim * dim, 0) {
    cells[get({0, 0})] = 1;
    cells[get({1, 0})] = 1;
    cells[get({1, -1})] = 2;
  }

  pos last() const noexcept { return {dim / 2, dim / 2}; }
  pos first() const noexcept { return {1, -1}; }

  static pos left(pos p) { return {p.x - 1, p.y}; }
  static pos down(pos p) { return {p.x, p.y + 1}; }
  static pos right(pos p) { return {p.x + 1, p.y}; }
  static pos up(pos p) noexcept { return {p.x, p.y - 1}; }

  typedef pos (*mov)(pos);

  void collect(pos* p, std::vector<pos>& ps, mov f, int times) const noexcept {
    while (times-- > 0) {
      *p = f(*p);
      ps.emplace_back(*p);
    }
  }

  std::vector<pos> circle() const noexcept {
    // left, down, right, up
    int sides[] = {2, 2, 3, 3};
    mov ms[] = {left, down, right, up};
    std::vector<pos> ps{};
    pos p = first();
    bool is_last{false};
    while (!is_last) {
      for (int i : {0, 1, 2, 3}) {
        collect(&p, ps, ms[i], sides[i]);
        if (p > last()) {
          is_last = true;
          break;
        }
        sides[i] += 2;
      }
    }
    return ps;
  }

  int set(pos p) {
    auto p1 = value({p.x, p.y + 1});
    auto p2 = value({p.x, p.y - 1});
    auto p3 = value({p.x - 1, p.y});
    auto p4 = value({p.x + 1, p.y});
    auto p5 = value({p.x + 1, p.y + 1});
    auto p6 = value({p.x + 1, p.y - 1});
    auto p7 = value({p.x - 1, p.y + 1});
    auto p8 = value({p.x - 1, p.y - 1});
    size_t i = get(p);
    cells[i] = p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8;
    // printf("(%d, %d) -> %d (%d,%d,%d,%d,%d,%d,%d,%d)\n", p.x, p.y, cells[i], p1, p2, p3, p4, p5, p6, p7, p8);
    return cells[i];
  }

  int fill_until(int t) {
    auto ps = circle();
    for (auto& p : ps) {
      int x = set(p);
      if (x > t) {
        return x;
      }
    }
    return 0;
  }
};

int day3(int);
int day3part2(int);
} // namespace aoc2017
