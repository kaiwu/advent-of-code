#pragma once

#include "common.h"

namespace aoc2015 {

struct grid {
  uint8_t* pool;

  struct unit {
    int x;
    int y;
  };

  grid(int x, int y) {
    pool = (uint8_t*)malloc(x * y);
    memset(pool, 0x0, x * y);
  }

  template <typename F, typename... Args>
  void traverse(unit u1, unit u2, F&& f, Args&&... args) {
    for (int i = u1.x; i <= u2.x; i++) {
      for (int j = u1.y; j <= u2.y; j++) {
        f(pool[i * j], std::forward<Args>(args)...);
      }
    }
  }

  void turn_on(unit u1, unit u2) {
    traverse(u1, u2, [](uint8_t& u) { u = 1; });
  }
  void turn_off(unit u1, unit u2) {
    traverse(u1, u2, [](uint8_t& u) { u = 0; });
  }
  void toggle(unit u1, unit u2) {
    traverse(u1, u2, [](uint8_t& u) { u = !u; });
  }
};

int day6(line_view);

} // namespace aoc2015
