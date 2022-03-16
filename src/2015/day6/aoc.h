#pragma once

#include "common.h"

namespace aoc2015 {

template <size_t N>
struct grid {
  static_assert(N > 0 && ((N & (N - 1)) == 0), "N must be power of 2");
  constexpr static size_t size = N * N / 64;

  uint64_t pool[size] = {0};

  struct unit {
    int x;
    int y;
  };

  void set(int x, int y) {
    uint64_t p = x * N + y;
    uint64_t r = p >> 6;
    uint64_t c = p & 63;
    uint64_t& byte = pool[r];
    uint64_t mask = 1 << c;
    byte |= mask;
  }

  void reset(int x, int y) {
    uint64_t p = x * N + y;
    uint64_t r = p >> 6;
    uint64_t c = p & 63;
    uint64_t& byte = pool[r];
    uint64_t mask = ~(1 << c);
    byte &= mask;
  }

  void toggle(int x, int y) {
    uint64_t p = x * N + y;
    uint64_t r = p >> 6;
    uint64_t c = p & 63;
    uint64_t& byte = pool[r];
    uint64_t mask = 1 << c;
    byte ^= mask;
  }

  int count() const noexcept {
    int total = 0;
    for (uint64_t i : pool) {
       total += __builtin_popcountll(i);
    }
    return total;
  }

  template <typename F, typename... Args>
  void traverse(unit u1, unit u2, F&& f, Args&&... args) {
    for (int i = u1.x; i <= u2.x; i++) {
      for (int j = u1.y; j <= u2.y; j++) {
        f(i, j, std::forward<Args>(args)...);
      }
    }
  }

  void turn_on(unit u1, unit u2) {
    traverse(u1, u2, [this](int i, int j) { set(i, j); });
  }
  void turn_off(unit u1, unit u2) {
    traverse(u1, u2, [this](int i, int j) { reset(i, j); });
  }
  void toggle(unit u1, unit u2) {
    traverse(u1, u2, [this](int i, int j) { toggle(i, j); });
  }
};

int day6(line_view);

} // namespace aoc2015
