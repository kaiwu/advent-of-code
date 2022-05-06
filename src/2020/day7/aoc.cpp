#include "aoc.h"
#include <algorithm>

namespace aoc2020 {

bool find_color(color_bag* bag, line_view color) {
  if (bag->color == color) {
    return true;
  } else {
    for (auto& p : bag->bags) {
      if (find_color(p.first, color)) {
        return true;
      }
    }
    return false;
  }
}

int day7(line_view file, const char* color) {
  bag_regulations rs;
  per_line(file, [&rs](line_view lv) {
    rs.parse(lv);
    return true;
  });

  int total{0};
  for (auto& b : rs.regulations) {
    if (!(b.second->color == color)) {
      total += int(find_color(b.second, color));
    }
  }

  return total;
}
} // namespace aoc2020
