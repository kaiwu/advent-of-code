#pragma once
#include "common.h"

namespace aoc2016 {

template <size_t W, size_t H>
struct grid {
  char cells[W * H] = {0};

  void print() {
    for (size_t i = 0; i < ARRAY_SIZE(cells); i++) {
      printf("%d", cells[i]);
      if (i % W == W - 1) {
        printf("\n");
      }
    }
    printf("\n");
  }

  void set(int x, int y) {
    for (int j = 0; j < y; j++) {
      for (int i = 0; i < x; i++) {
        cell(i, j) = 1;
      }
    }
  }

  char& cell(int x, int y) { return cells[y * W + x]; }
  char& prev_h(int x, int y) {
    int n = x == 0 ? W - 1 : x - 1;
    return cell(n, y);
  }

  void rotate_h(int y) {
    char last = cell(W - 1, y);
    for (int x = W - 1; x > 0; x--) {
      cell(x, y) = prev_h(x, y);
    }
    cell(0, y) = last;
  }

  void rotate_h(int y, int t) {
    t %= W;
    while (t-- > 0) {
      rotate_h(y);
    }
  }

  char& prev_v(int x, int y) {
    int n = y == 0 ? H - 1 : y - 1;
    return cell(x, n);
  }

  void rotate_v(int x) {
    char last = cell(x, H - 1);
    for (int y = H - 1; y > 0; y--) {
      cell(x, y) = prev_v(x, y);
    }
    cell(x, 0) = last;
  }

  void rotate_v(int x, int t) {
    t %= H;
    while (t-- > 0) {
      rotate_v(x);
    }
  }
};

int day8(line_view);
} // namespace aoc2016
