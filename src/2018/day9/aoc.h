#pragma once
#include "common.h"
#include <vector>

namespace aoc2018 {

struct marble {
  marble* prev = nullptr;
  marble* next = nullptr;
  size_t value = 0;
};

struct marble_circle {
  std::vector<marble> marbles;
  std::vector<size_t> players;
  marble* current;
  size_t point;

  void insert(marble* p, marble* n, marble* x) noexcept {
    p->next = x;
    x->next = n;
    x->prev = p;
    n->prev = x;
  }

  size_t high() const noexcept {
    size_t score = 0;
    for (auto& p : players) {
      score = std::max(score, p);
    }
    return score;
  }

  void remove(marble* x) noexcept {
    x->prev->next = x->next;
    x->next->prev = x->prev;
  }

  marble* next(marble* c, int n) noexcept {
    while (n-- > 0) {
      c = c->next;
    }
    return c;
  }

  marble* prev(marble* c, int n) noexcept {
    while (n-- > 0) {
      c = c->prev;
    }
    return c;
  }

  void print() {
    marble* x = &marbles[0];
    while (true) {
      if (x->next == &marbles[0]) {
        printf("%zu\n", x->value);
        break;
      } else {
        printf("%zu -> ", x->value);
        x = x->next;
      }
    }
  }

  marble_circle(size_t n, size_t p) : marbles(n + 1), players(p) {
    marbles[0].next = &marbles[1];
    marbles[0].prev = &marbles[1];
    marbles[0].value = 0;

    marbles[1].prev = &marbles[0];
    marbles[1].next = &marbles[0];
    marbles[1].value = 1;

    current = &marbles[1];
    point = 1;
  }

  void alloc(int a, int b, int c) {
    size_t i = 2;
    while (point < marbles.size() - 1) {
      // print();
      size_t p = point + 1;
      marbles[p].value = p;

      if (p % c == 0) {
        marble* m = prev(current, b);
        players[i - 1] += p + m->value;
        current = m->next;
        remove(m);
      } else {
        marble* m = next(current, a);
        insert(m, m->next, &marbles[p]);
        current = &marbles[p];
      }
      point = p;
      i = i == players.size() ? 1 : i + 1;
    }
  }
};

size_t day9(size_t players, size_t point);

} // namespace aoc2018
