#pragma once
#include "common.h"
#include <algorithm>
#include <vector>

namespace aoc2015 {

struct Role {
  int hitpoints;
  int damage;
  int armor;
  int cost;
};

struct RPG {
  struct item {
    line_view name;
    int cost;
    int damage;
    int armor;
  };

  // 1 in 5
  item weapons[5] = {
      {"dagger", 8, 4, 0},     {"shortsword", 10, 5, 0}, {"warhammer", 25, 6, 0},
      {"longsword", 40, 7, 0}, {"greataxe", 74, 8, 0},
  };

  // 0, 1 in 5
  item armors[5] = {
      {"leather", 13, 0, 1},    {"chainmail", 31, 0, 2},  {"splintmail", 53, 0, 3},
      {"bandedmail", 75, 0, 4}, {"platemail", 102, 0, 5},
  };

  // 0, 1, 2 in 6
  item rings[6] = {
      {"ring1", 25, 1, 0}, {"ring2", 50, 2, 0}, {"ring3", 100, 3, 0},
      {"ring4", 20, 0, 1}, {"ring5", 40, 0, 2}, {"ring6", 80, 0, 3},
  };

  struct three {
    int i1;
    int i2;
    int i3;
  };

  // backtrace
  void shop(int i, three& t1, three& t2, std::vector<item>& is) {
    if (i == 3) {

    }
  }

  std::vector<Role> shop(Role r) {
    std::vector<item> is;
    std::vector<Role> rs;
    three t1;
    three t2;
    shop(0, t1, t2, is);
    std::transform(is.begin(), is.end(), rs.begin(), [&r](const item& i) -> Role {
      Role x = r;
      x.cost += i.cost;
      x.armor += i.armor;
      x.damage += i.damage;
      return x;
    });
    return rs;
  }

  bool battle(Role& r1, Role& r2) {
    while (r1.hitpoints > 0 && r2.hitpoints > 0) {
      r2.hitpoints -= (r1.damage - r2.armor) > 0 ? r1.damage - r2.armor : 1;
      r1.hitpoints -= (r2.damage - r1.armor) > 0 ? r2.damage - r1.armor : 1;
    }
    return r1.hitpoints > 0 || r2.hitpoints <= 0;
  }
};

int day21();

} // namespace aoc2015
