#pragma once

#include "common.h"

namespace aoc2020 {

struct seat {
  enum {
    rows = 128,
    cols = 8,
  };

  int row;
  int col;

  int id() const noexcept { return row * 8 + col; }
  bool operator<(const seat& other) { return id() < other.id(); }

  seat(int r, int c) : row(r), col(c) {}

  // F lower
  // B higher
  // L lower
  // R higher
  seat(line_view lv) {
    const char* p = lv.line;
    int minr = 0;
    int maxr = 128;
    int minc = 0;
    int maxc = 8;
    while (p < lv.line + lv.length) {
      int midr = (maxr + minr) / 2;
      if (*p == 'F') {
        maxr = midr;
      }
      if (*p == 'B') {
        minr = midr;
      }
      int midc = (maxc + minc) / 2;
      if (*p == 'L') {
        maxc = midc;
      }
      if (*p == 'R') {
        minc = midc;
      }
      p++;
    }
    row = minr;
    col = minc;
    // printf("%d %d\n", row, col);
  }
};

int day5(line_view);

} // namespace aoc2020
