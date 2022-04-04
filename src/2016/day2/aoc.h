#pragma once
#include "common.h"

namespace aoc2016 {

struct keybad {
  enum move {
    up,
    right,
    down,
    left,
  };

  int keys[9][4] = {
      {1, 2, 4, 1}, {2, 3, 5, 1}, {3, 3, 6, 2}, {1, 5, 7, 4}, {2, 6, 8, 4},
      {3, 6, 9, 5}, {4, 8, 7, 7}, {5, 9, 8, 7}, {6, 9, 9, 8},
  };

  int touch(int i, char c) {
    static int az[] = {
        INT_MAX, INT_MAX, INT_MAX,
        2,                                                                // D
        INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 3, // L
        INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
        1,                   // R
        INT_MAX, INT_MAX, 0, // U
        INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
    };
    return keys[i - 1][az[c - 'A']];
  }

  int touch(int i, const char* p) {
    while (*p >= 'A' && *p <= 'Z') {
      i = touch(i, *p);
      p++;
    }
    return i;
  }
};

int day2(line_view);

} // namespace aoc2016
