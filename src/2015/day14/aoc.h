#pragma once
#include "common.h"
#include <vector>

namespace aoc2015 {

struct reindeer {
  line_view name;
  int speed;
  int fly_seconds;
  int rest_seconds;

  friend std::ostream& operator<<(std::ostream& o, const reindeer& r) {
    o << r.name << " " << r.speed << " " << r.fly_seconds << " " << r.rest_seconds;
    return o;
  }
};

struct olympics {
  std::vector<reindeer> reindeers;

  int get_number(const char* p) {
    int d{0};
    while (*p != ' ') {
      d = d * 10 + *p - '0';
      p++;
    }
    return d;
  }

  int kilometers(const reindeer& r, int s) {
    int period = r.fly_seconds + r.rest_seconds;
    int x = s / period;
    int y = s % period;
    if (y > r.fly_seconds) {
      y = r.fly_seconds;
    }
    return x * (r.speed * r.fly_seconds) + r.speed * y;
  }

  std::pair<line_view, int> best(int s) {
    std::pair<line_view, int> d{{}, INT32_MIN};
    for (auto& r : reindeers) {
      auto x = kilometers(r, s);
      std::cout << r.name << ": " << x << std::endl;
      if (x > d.second) {
        d = {r.name, x};
      }
    }
    return d;
  }

  void parse(line_view lv) {
    const char* p1 = lv.contains("can");
    const char* p2 = lv.contains("for");
    line_view tail = {p2 + 3, lv.line + lv.length};
    const char* p3 = tail.contains("for");
    reindeer r;
    r.name = line_view{lv.line, p1 - 1};
    r.speed = get_number(p1 + 8);
    r.fly_seconds = get_number(p2 + 4);
    r.rest_seconds = get_number(p3 + 4);
    // std::cout << r << std::endl;
    reindeers.push_back(r);
  }
};

int day14(line_view, int);
} // namespace aoc2015
