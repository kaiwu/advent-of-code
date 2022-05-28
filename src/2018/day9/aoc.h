#pragma once
#include "common.h"
#include <vector>

namespace aoc2018 {

struct marble {
  marble* prev = nullptr;
  marble* next = nullptr;
  int value = 0;
};

struct marble_circle {
  std::vector<marble> marbles;
  std::vector<int> players;
  marble* current;
  int point;

  void insert(marble& p, marble& n, marble& x) noexcept {
    p.next = &x;
    x.next = &n;
    x.prev = &p;
    n.prev = &x;
  }

  int high() const noexcept {
    int score = 0;
    for (auto& p : players) {
      score = std::max(score, p);
    }
    return score;
  }

  void remove(marble& x) noexcept {
    x.prev->next = x.next;
    x.next->prev = x.prev;
  }

  marble& next(marble* c, int n) noexcept {
    while (n-- > 0) {
      c = c->next;
    }
    return *c;
  }

  marble& prev(marble* c, int n) noexcept {
    while (n-- > 0) {
      c = c->prev;
    }
    return *c;
  }

  marble_circle(int n, int p) : marbles(n + 1), players(p) {
    marbles[0].next = &marbles[1];
    marbles[0].prev = &marbles[1];
    marbles[0].value = 0;

    marbles[1].prev = &marbles[0];
    marbles[1].next = &marbles[0];
    marbles[1].value = 1;

    current = &marbles[1];
    point = 1;
  }

  void alloc(int x) {
    int i = 2;
    while (point < int(marbles.size())) {
      int p = point + 1;
      marbles[p].value = p;

      if (p % x == 0) {
        marble& m = prev(current, 7);
        players[i - 1] += p + m.value;
        current = m.next;
        remove(m);
      } else {
        marble& m = next(current, 1);
        insert(m, *m.next, marbles[p]);
        current = &marbles[p];
      }
      point = p;
      i = i == int(players.size()) ? 1 : i + 1;
    }
  }
};

int day9(int players, int point);

} // namespace aoc2018
