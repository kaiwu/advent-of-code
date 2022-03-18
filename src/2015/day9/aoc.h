#pragma once
#include "common.h"
#include <map>
#include <vector>

namespace aoc2015 {

struct location {
  line_view name;
  std::map<location*, int> routes;
};

struct world_day9 {
  std::vector<location*> locations;

  location* find(line_view l) {
    for (auto city : locations) {
      if (city->name == l) {
        return city;
      }
    }
    locations.emplace_back(new location{l, {}});
    return locations.back();
  }

  int distance(line_view l) const noexcept {
    int d{0};
    const char* p = l.line;
    while (p < l.line + l.length) {
      d = d * 10 + *p++ - '0';
    }
    return d;
  }

  void parse(line_view r) {
    const char* p1 = r.contains("to");
    const char* p2 = r.contains("=");
    location* l1 = find({r.line, p1 - 1});
    location* l2 = find({p1 + 3, p2 - 1});
    int d = distance({p2 + 2, r.line + r.length - 1});
    l1->routes.insert({l2, d});
    l2->routes.insert({l1, d});
  }

  void check() const noexcept {
    for (auto city : locations) {
      for (auto& kv : city->routes) {
        std::cout << city->name << " -> " << kv.first->name << ": " << kv.second << std::endl;
      }
    }
  }
};

int day9(line_view);

} // namespace aoc2015
