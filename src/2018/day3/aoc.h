#pragma once
#include "common.h"
#include <vector>

namespace aoc2018 {

struct claim {
  int id;
  int x;
  int y;
  int width;
  int height;
};

struct fabric {
  // 0 ... 999
  uint16_t claims[1000 * 1000] = {0};

  void apply(const claim& c) {
    for (int x = c.x; x < c.x + c.width; x++) {
      for (int y = c.y; y < c.y + c.height; y++) {
        claims[y * 1000 + x] += 1;
      }
    }
  }

  int count(int x) {
    int total{0};
    for (auto c : claims) {
      if (c > x) {
        total += 1;
      }
    }
    return total;
  }

  bool overlap(const claim& c) {
    for (int x = c.x; x < c.x + c.width; x++) {
      for (int y = c.y; y < c.y + c.height; y++) {
        if (claims[y * 1000 + x] > 1) {
          return true;
        }
      }
    }
    return false;
  }

  void get_number(const char** pp, int* is[], int i) {
    *is[i] = 0;
    const char* p = *pp;
    while (*p >= '0' && *p <= '9') {
      *is[i] = *is[i] * 10 + *p - '0';
      p++;
    }
    *pp = p;
  }

  void parse(line_view lv, std::vector<claim>& cs) {
    claim c;
    int* is[] = {&c.id, &c.x, &c.y, &c.width, &c.height};
    int i{0};
    const char* p = lv.line;
    while (p < lv.line + lv.length) {
      if (*p >= '0' && *p <= '9') {
        get_number(&p, is, i++);
      }
      p++;
    }
    apply(c);
    cs.push_back(c);
  }
};

std::pair<int, int> day3(line_view, int);

} // namespace aoc2018
