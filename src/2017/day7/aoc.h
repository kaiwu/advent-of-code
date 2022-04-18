#pragma once
#include "common.h"
#include <vector>

namespace aoc2017 {

struct disc {
  line_view name;
  int weight;
  int total = 0;
  std::vector<disc*> subs;
  const char* xp = nullptr;

  const char* get_number(const char* p, int* d) {
    *d = 0;
    while (*p >= '0' && *p <= '9') {
      *d = *d * 10 + *p - '0';
      p++;
    }
    return p;
  }

  disc(line_view lv, const char* p) {
    name = {lv.line, p - 1};
    p = get_number(p + 1, &weight) + 5;
    if (p < lv.line + lv.length) {
      xp = p;
    }
  }
};

void day7(line_view, char[]);

} // namespace aoc2017
