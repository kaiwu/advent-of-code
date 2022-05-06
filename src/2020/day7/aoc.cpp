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

void count_color(color_bag* bag, int* total) {
  for (auto& b : bag->bags) {
    *total += b.second;
    for (int i = 0; i < b.second; i++) {
      count_color(b.first, total);
    }
  }
}

std::pair<int, int> day7(line_view file, const char* color) {
  bag_regulations rs;
  per_line(file, [&rs](line_view lv) {
    rs.parse(lv);
    return true;
  });

  int t0{0};
  for (auto& b : rs.regulations) {
    if (!(b.second->color == color)) {
      t0 += int(find_color(b.second, color));
    }
  }

  int t1{0};
  count_color(rs.regulations[color], &t1);

  return {t0, t1};
}
} // namespace aoc2020
