#pragma once
#include "common.h"

namespace aoc2017 {

struct memory_bank {
  int banks[16];

  void get_number(const char** pp, int* d) {
    const char* p = *pp;
    *d = 0;
    while (*p >= '0' && *p <= '9') {
      *d = *d * 10 + *p - '0';
      p++;
    }
    *pp = p;
  }

  memory_bank(line_view lv) {
    const char* p = lv.line;
    int i{0};
    while (p < lv.line + lv.length) {
      if (*p >= '0' && *p <= '9') {
        get_number(&p, &banks[i++]);
      }
      p++;
    }
  }

  bool operator<(const memory_bank& m) const noexcept {
    for (size_t i = 0; i < ARRAY_SIZE(banks); i++) {
      if (banks[i] < m.banks[i]) {
        return true;
      }
      if (banks[i] > m.banks[i]) {
        return false;
      }
    }
    return false;
  }

  int highest(int* d) const noexcept {
    int max{INT32_MIN};
    int index{0};
    for (size_t i = 0; i < ARRAY_SIZE(banks); i++) {
      if (banks[i] > max) {
        max = banks[i];
        index = i;
      }
    }
    *d = max;
    return index;
  }

  void distribute(size_t i, int x) {
    banks[i] = 0;
    while (x > 0) {
      i = (i == ARRAY_SIZE(banks) - 1) ? 0 : i + 1;
      banks[i] += 1;
      x -= 1;
    }
  }
};

int day6(line_view);

} // namespace aoc2017
