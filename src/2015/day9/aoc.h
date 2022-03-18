#pragma once
#include "common.h"
#include <map>
#include <set>
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

  // backtrace
  void plan(location* city, std::set<location*>& visited, std::vector<int>& distances, int* d) {
    if (visited.size() == locations.size()) {
      // std::cout << city->name << std::endl;
      distances.push_back(*d);
      return;
    }
    for (auto& kv : city->routes) {
      auto it = visited.find(kv.first);
      if (it != visited.end()) {
        continue;
      } else { // not visited
        // std::cout << city->name << " -> ";
        location* next = kv.first;
        visited.insert(next);
        *d += kv.second;
        plan(next, visited, distances, d);
        visited.erase(next);
        *d -= kv.second;
      }
    }
  }

  std::pair<int, int> minmax(const std::vector<int>& ds) {
    int d1 = INT32_MAX;
    int d2 = INT32_MIN;
    for (auto x : ds) {
      if (x < d1) {
        d1 = x;
      }
      if (x > d2) {
        d2 = x;
      }
    }
    return {d1, d2};
  }

  std::pair<int, int> plan(location* city) {
    std::vector<int> ds;
    std::set<location*> visited{city};
    int d{0};
    plan(city, visited, ds, &d);
    return minmax(ds);
  }
};

std::pair<int, int> day9(line_view);

} // namespace aoc2015
