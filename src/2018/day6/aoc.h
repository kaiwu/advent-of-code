#pragma once
#include "common.h"
#include <algorithm>
#include <math.h>
#include <utility>
#include <vector>

namespace aoc2018 {

struct coordinate {
  int x = 0;
  int y = 0;

  coordinate(int xx, int yy) : x(xx), y(yy) {}
  coordinate(line_view lv) {
    const char* p = lv.line;
    int* d[] = {&x, &y};
    int i{0};
    while (p < lv.line + lv.length) {
      if (*p >= '0' && *p <= '9') {
        get_number(&p, d[i++]);
      }
      p++;
    }
  }

  void get_number(const char** pp, int* d) {
    const char* p = *pp;
    *d = 0;
    while (*p >= '0' && *p <= '9') {
      *d = *d * 10 + *p - '0';
      p++;
    }
    *pp = p;
  }

  int distance(coordinate c = coordinate{0, 0}) const noexcept { return std::abs(x - c.x) + std::abs(y - c.y); }
  coordinate right(int d) const noexcept { return {x + d, y}; }
  coordinate up(int d) const noexcept { return {x, y - d}; }
  coordinate left(int d) const noexcept { return {x - d, y}; }
  coordinate down(int d) const noexcept { return {x, y + d}; }
  typedef coordinate (coordinate::*move)(int) const;

  bool operator<(const coordinate& c) const noexcept {
    int d1 = distance();
    int d2 = c.distance();
    return d1 < d2 ? true : (d1 > d2 ? false : (x < c.x ? true : (x > c.x ? false : y < c.y)));
  }

  template <typename F, typename G, typename... Args>
  void traverse(F&& f, G&& g, Args&&... args) const noexcept {
    // right, up, left, down
    auto next = [](int i, coordinate c) -> coordinate {
      move fs[] = {&coordinate::right, &coordinate::up, &coordinate::left, &coordinate::down};
      return (c.*(fs[i]))(1);
    };
    int steps[] = {1, 1, 2, 2};
    size_t i{0};
    coordinate c = *this;
    bool stop{false};
    while (!stop) {
      int s = i % 4;
      for (int x = 0; x < steps[s] && !stop; x++) {
        c = next(s, c);
        stop = !f(i / 4, c, std::forward<Args>(args)...);
      }
      steps[s] += 2;
      i++;
      stop = stop || ((i % 4 == 0) && g());
    }
  }
};

struct space_board {
  // -1 no one
  // -2 same distance
  struct point {
    int id = -1;
    int distance = INT32_MAX;
  };

  int width;
  int height;
  std::vector<point> ps;
  space_board(int x, int y) : width(x), height(y), ps(x * y){};

  int size() const noexcept { return width * height; }

  void print() const noexcept {
    for (size_t i = 0; i < ps.size(); i++) {
      if (i % width == 0) {
        printf("\n");
      }
      char c = ps[i].id >= 0 ? 'a' + ps[i].id : '.';
      if (ps[i].distance == 0) {
        c = c - 32;
      }
      std::cout << c;
    }
  }

  int safe(int d, const std::vector<coordinate>& cs) {
    int total{0};
    for (size_t i = 0; i < ps.size(); i++) {
      coordinate c{int(i % width), int(i / width)};
      int sum{0};
      std::for_each(cs.begin(), cs.end(), [&sum, &c](coordinate x) { sum += c.distance(x); });
      total += int(sum < d);
    }
    return total;
  }

  void count(std::vector<int>& area) const noexcept {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        auto& p = ps[y * width + x];
        if (p.id == -2) {
          continue;
        }
        if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
          area[p.id] = INT32_MAX;
        }
        if (area[p.id] < INT32_MAX) {
          area[p.id] += 1;
        }
      }
    }
  }
};

std::pair<int, int> day6(line_view, int);

} // namespace aoc2018
