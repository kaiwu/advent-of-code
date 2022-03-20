#pragma once

#include "common.h"
#include <vector>

namespace aoc2015 {

struct ingredient {
  line_view name;
  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;

  friend std::ostream& operator<<(std::ostream& o, const ingredient& i) {
    o << i.name << " " << i.capacity << " " << i.durability << " " << i.flavor << " " << i.texture << " " << i.calories;
    return o;
  }
};

struct recipe {
  std::vector<ingredient> ingredients;

  int score(const std::vector<int>& is) {
    int capacity = 0;
    int durability = 0;
    int flavor = 0;
    int texture = 0;
    for (size_t i = 0; i < ingredients.size(); i++) {
      capacity += is[i] * ingredients[i].capacity;
      durability += is[i] * ingredients[i].durability;
      flavor += is[i] * ingredients[i].flavor;
      texture += is[i] * ingredients[i].texture;
    }
    if (capacity < 0 || durability < 0 || flavor < 0 || texture < 0) {
      return 0;
    }
    return capacity * durability * flavor * texture;
  }

  // backtrace
  void measure(int total, size_t index, std::vector<int>& combos, int* best) {
    if (index == ingredients.size() - 1) { // last ingredient
      combos.push_back(total);
      int s = score(combos);

      // std::cout << "{" << s << " -> ";
      // for (auto i : {0, 1, 2, 3}) {
      //   std::cout << ingredients[i].name << ": " << combos[i] << " ";
      // }
      // std::cout << "}" << std::endl;

      if (s > 0 && s > *best) {
        *best = s;
      }
      combos.pop_back();
      return;
    }

    for (int x = 1; x < total; x++) {
      combos.push_back(x);
      measure(total - x, index + 1, combos, best);
      combos.pop_back();
    }
  }

  int get_number(const char* p) {
    int d{0};
    int sign{1};
    if (*p == '-') {
      sign = -1;
      p++;
    }
    while ((*p) >= '0' && (*p) <= '9') {
      d = d * 10 + *p - '0';
      p++;
    }
    return sign * d;
  }

  void parse(line_view line) {
    static const char* cs[] = {"capacity", "durability", "flavor", "texture", "calories"};
    const char* p0 = line.contains(":");
    ingredient x{{line.line, p0}, 0, 0, 0, 0, 0};
    int* xs[] = {&x.capacity, &x.durability, &x.flavor, &x.texture, &x.calories};

    for (size_t i = 0; i < ARRAY_SIZE(cs); i++) {
      const char* p = line.contains(cs[i]);
      *xs[i] = get_number(p + strlen(cs[i]) + 1);
    }
    // std::cout << x << std::endl;
    ingredients.push_back(x);
  }
};

int day15(line_view);

} // namespace aoc2015
