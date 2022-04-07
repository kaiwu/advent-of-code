#pragma once
#include "common.h"
#include <algorithm>
#include <functional>
#include <vector>

namespace aoc2019 {

struct day3point {
  int x;
  int y;

  int distance() const noexcept { return std::abs(x) + std::abs(y); }
  bool operator<(const day3point& other) const noexcept { return distance() < other.distance(); }
};

struct wire {
  struct part {
    enum dir_t {
      up,
      right,
      down,
      left,
    } dir;
    int distance;
  };

  day3point mov(day3point p, part pa) const noexcept {
    auto addy = [&p](int d) -> day3point { return {p.x, p.y + d}; };
    auto addx = [&p](int d) -> day3point { return {p.x + d, p.y}; };
    auto suby = [&p](int d) -> day3point { return {p.x, p.y - d}; };
    auto subx = [&p](int d) -> day3point { return {p.x - d, p.y}; };
    std::function<day3point(int)> fs[] = {addy, addx, suby, subx};
    return fs[int(pa.dir)](pa.distance);
  }

  struct line {
    int id;
    line_view label;
    day3point a;
    day3point b;
    int length;
  };

  std::vector<line> psh;
  std::vector<line> psv;
  std::vector<line> ps;

  void sort() {
    std::sort(psh.begin(), psh.end(),
              [](const line& l1, const line& l2) { return std::abs(l1.a.y) < std::abs(l2.a.y); });
    std::sort(psv.begin(), psv.end(),
              [](const line& l1, const line& l2) { return std::abs(l1.a.x) < std::abs(l2.a.x); });
  }

  void get_part(const char** pp, int* d) {
    *d = 0;
    const char* p = *pp + 1;
    while (*p >= '0' && *p <= '9') {
      *d = *d * 10 + *p - '0';
      p++;
    }
    *pp = p;
  }

  void parse(line_view lv, day3point* cp) {
    part p;
    const char* p1 = lv.line;
    int i{0};
    auto make_part = [&i, &p, &p1, cp, this](part::dir_t d) {
      p.dir = d;
      const char* p0 = p1;
      get_part(&p1, &p.distance);
      day3point a = *cp;
      *cp = mov(*cp, p);
      line l{i++, {p0, p1}, a, *cp, p.distance};
      ps.push_back(l);
      if (d == part::right || d == part::left) {
        psh.push_back(l);
      }
      if (d == part::up || d == part::down) {
        psv.push_back(l);
      }
    };
    while (p1 < lv.line + lv.length) {
      switch (*p1) {
      case 'R':
        make_part(part::right);
        break;
      case 'L':
        make_part(part::left);
        break;
      case 'U':
        make_part(part::up);
        break;
      case 'D':
        make_part(part::down);
        break;
      default:
        break;
      }
      p1++;
    }
  }
};

std::pair<int, int> day3(line_view);

} // namespace aoc2019
