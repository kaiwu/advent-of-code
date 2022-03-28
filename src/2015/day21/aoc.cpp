#include "aoc.h"

namespace aoc2015 {

std::pair<int, int> day21() {
  Role me{100, 0, 0, 0};
  Role boss{100, 8, 2, 0};
  RPG game;

  int m1{INT32_MAX};
  int m2{INT32_MIN};
  std::vector<Role> rs = game.shop(me);
  std::for_each(rs.begin(), rs.end(), [&game, &boss, &m1, &m2](Role& r) {
    Role b = boss;
    if (game.battle(r, b)) {
      if (r.cost < m1) {
        m1 = r.cost;
      }
    } else {
      if (r.cost > m2) {
        m2 = r.cost;
      }
    }
  });
  return {m1, m2};
}
} // namespace aoc2015
