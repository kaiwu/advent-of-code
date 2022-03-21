#pragma once

#include "common.h"

namespace aoc2015 {

struct neolight {
  constexpr static size_t size = 100 * 100;
  uint8_t bs[size] = {0};

  int count() const noexcept {
    int d{0};
    for (auto i : bs) {
      if (i > 0) {
        d += 1;
      }
    }
    return d;
  }

  void turn(int x, int y, int v) { bs[y * 100 + x] = v; }

  bool on(int x, int y) const noexcept {
    if (x < 0 || y < 0 || x > 99 || y > 99) {
      return false;
    }
    return bs[y * 100 + x] > 0;
  }

  int count(int x, int y) const noexcept {
    int d{0};
    for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
        if (!(i == 0 && j == 0)) {
          d += on(x + i, y + j) ? 1 : 0;
        }
      }
    }
    return d;
  }
};

struct yard {
  neolight* lights = new neolight;

  void transform(int x, int y, neolight* g, neolight* n) {
    if (g->on(x, y)) {
      int v = 0;
      int neighbors = g->count(x, y);
      if (neighbors == 2 || neighbors == 3) {
        v = 1;
      }
      n->turn(x, y, v);
    } else {
      int v = 0;
      int neighbors = g->count(x, y);
      if (neighbors == 3) {
        v = 1;
      }
      n->turn(x, y, v);
    }
  }

  neolight* next(neolight* g) {
    neolight* n = new neolight;
    for (int x = 0; x < 100; x++) {
      for (int y = 0; y < 100; y++) {
        transform(x, y, g, n);
      }
    }
    return n;
  }

  void turns(int i) {
    while (i-- > 0) {
      lights = next(lights);
    }
  }

  int count() { return lights != nullptr ? lights->count() : 0; }

  void parse(line_view file) {
    int x = 0;
    int y = 0;
    const char *p = file.line;
    while (p != file.line + file.length) {
      if (*p == '#') {
        lights->turn(x++, y, 1);
      }
      if (*p == '.') {
        lights->turn(x++, y, 0);
      }
      if (*p == '\n') {
        x = 0;
        y += 1;
      }
      p++;
    }
  }
};

int day18(line_view, int);

} // namespace aoc2015
