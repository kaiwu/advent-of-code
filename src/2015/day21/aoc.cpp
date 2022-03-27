#include "aoc.h"

namespace aoc2015 {

int day21() {
  Role me{100, 0, 0, 0};
  Role boss{100, 8, 2, 0};
  RPG game;

  int money{INT32_MAX};
  std::vector<Role> rs = game.shop(me);
  std::for_each(rs.begin(), rs.end(), [&game, &boss, &money](Role& r) {
    Role b = boss;
    if (game.battle(r, b)) {
      if (r.cost < money) {
        money = r.cost;
      }
    }
  });
  return money;
}

} // namespace aoc2015
