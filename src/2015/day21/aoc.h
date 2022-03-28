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
    const char* name;
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
  item armors[6] = {
      {"leather", 13, 0, 1},    {"chainmail", 31, 0, 2},  {"splintmail", 53, 0, 3},
      {"bandedmail", 75, 0, 4}, {"platemail", 102, 0, 5}, {"none", 0, 0, 0},
  };

  // 0, 1, 2 in 6
  item rings[7] = {
      {"ring1", 25, 1, 0}, {"ring2", 50, 2, 0}, {"ring3", 100, 3, 0}, {"ring4", 20, 0, 1},
      {"ring5", 40, 0, 2}, {"ring6", 80, 0, 3}, {"none", 0, 0, 0},
  };

  bool has_same_ring(std::vector<item*> is) {
    int x[ARRAY_SIZE(rings)] = {0};
    for (item* i : is) {
      line_view lv{i->name};
      const char* p = lv.contains("ring");
      if (p != nullptr && ++(x[*(p + 4) - '1']) > 1) {
        return true;
      }
    }
    return false;
  }

  // backtrace
  void shop(size_t i, std::vector<item*>& v, std::vector<Role>& rs, const Role& r) {
    static item* items[] = {weapons, armors, rings, rings};
    static size_t sizes[] = {ARRAY_SIZE(weapons), ARRAY_SIZE(armors), ARRAY_SIZE(rings), ARRAY_SIZE(rings)};
    if (i < ARRAY_SIZE(items)) {
      item* is = items[i];
      for (size_t x = 0; x < sizes[i]; x++) {
        v.push_back(&is[x]);
        shop(i + 1, v, rs, r);
        v.pop_back();
      }
    } else {
      if (!has_same_ring(v)) {
        Role x = r;
        std::for_each(v.begin(), v.end(), [&x](item* i) {
          x.cost += i->cost;
          x.armor += i->armor;
          x.damage += i->damage;
        });
        rs.push_back(x);
      }
    }
  }

  std::vector<Role> shop(Role r) {
    std::vector<item*> is;
    std::vector<Role> rs;
    shop(0, is, rs, r);
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

std::pair<int,int> day21();

} // namespace aoc2015
