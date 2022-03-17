#pragma once

#include "common.h"

namespace aoc2015 {

template <size_t N>
struct grid {
  constexpr static size_t size = N * N / 64 + 1;

  uint64_t pool[size] = {0};

  struct unit {
    int x;
    int y;
  };

  void set(int x, int y) {
    uint64_t p = y * N + x;
    uint64_t r = p >> 6;
    uint64_t c = p & 63;
    uint64_t& byte = pool[r];
    uint64_t mask = 1ll << c;
    byte |= mask;
  }

  void reset(int x, int y) {
    uint64_t p = y * N + x;
    uint64_t r = p >> 6;
    uint64_t c = p & 63;
    uint64_t& byte = pool[r];
    uint64_t mask = ~(1ll << c);
    byte &= mask;
  }

  void toggle(int x, int y) {
    uint64_t p = y * N + x;
    uint64_t r = p >> 6;
    uint64_t c = p & 63;
    uint64_t& byte = pool[r];
    uint64_t mask = 1ll << c;
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

  std::pair<unit, unit> parse(const char* p1, const char* p2) {
    unit u1;
    unit u2;
    int* is[] = {&u1.x, &u1.y, &u2.x, &u2.y};
    int i = 0;
    const char* p = p1;
    while (i < 4 && p < p2) {
      int x = 0;
      while (*p >= '0' && *p <= '9') {
        x = x * 10 + *p - '0';
        p++;
      }
      *is[i++] = x;
      while (*p < '0' || *p > '9') {
        p++;
      }
    }

    return {u1, u2};
  }

  void parse(line_view lv) {
    static struct _ {
      void (grid::*action)(unit, unit);
      const char* key;
    } keywords[] = {{&grid::toggle, "toggle"}, {&grid::turn_off, "turn off"}, {&grid::turn_on, "turn on"}};

    for (auto k : keywords) {
      if (lv.contains(k.key)) {
        const char* p1 = lv.line + strlen(k.key) + 1;
        const char* p2 = lv.line + lv.length;
        auto p = parse(p1, p2);
        (this->*k.action)(p.first, p.second);
        break;
      }
    }
  }
};

int day6(line_view);

} // namespace aoc2015
