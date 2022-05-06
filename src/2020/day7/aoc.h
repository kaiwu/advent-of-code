#pragma once
#include "common.h"
#include <unordered_map>
#include <vector>

namespace aoc2020 {

struct color_bag {
  line_view color;
  std::vector<std::pair<color_bag*, int>> bags;
};

struct bag_regulations {
  std::unordered_map<line_view, color_bag*> regulations;

  void get_number(const char** pp, int* d) {
    const char* p = *pp;
    *d = 0;
    while (*p >= '0' && *p <= '9') {
      *d = *d * 10 + *p - '0';
      p++;
    }
    *pp = p;
  }

  std::pair<color_bag*, int> get_bag(const char* p1, const char* p2) {
    int d{0};
    get_number(&p1, &d);
    line_view color = {d > 0 ? p1 + 1 : p1, *(p2 - 1) == 's' ? p2 - 5 : p2 - 4};
    color_bag* bag = nullptr;
    auto it = regulations.find(color);
    if (it == regulations.end()) {
      bag = new color_bag{color, {}};
      regulations.insert({color, bag});
    } else {
      bag = it->second;
    }
    return {bag, d};
  }

  void parse(line_view lv) {
    const char* p1 = lv.line;
    const char* p2 = lv.line + lv.length;
    const char* p = lv.contains("contain");
    auto pa1 = get_bag(p1, p - 1);
    p1 = p + 8;
    p = p1;
    while (p < p2) {
      if (*p == ',' || *p == '.') {
        pa1.first->bags.push_back(get_bag(p1, p));
        p1 = p + 2;
      }
      p++;
    }
  }
};

int day7(line_view, const char*);
} // namespace aoc2020
