#include "aoc.h"
#include <algorithm>

namespace aoc2018 {

int day6(line_view file) {
  std::vector<coordinate> cs;
  int maxx{INT32_MIN};
  int maxy{INT32_MIN};

  per_line(file, [&cs, &maxx, &maxy](line_view lv) {
    coordinate c(lv);
    cs.push_back(c);
    maxx = std::max(maxx, c.x);
    maxy = std::max(maxx, c.y);
    return true;
  });

  std::sort(cs.begin(), cs.end());
  space_board b{maxx + 1, maxy + 1};

  for (size_t i = 0; i < cs.size(); i++) {
    coordinate& c = cs[i];
    auto& p = b.ps[c.y * b.rows + c.x];
    p.id = i;
    p.distance = 0;

    std::vector<int> total = {0};
    c.traverse([&total, &b, &c](int lap, int dir, coordinate x) { return true; },
               [&total]() { return total[total.size() - 1] == 0; });
  }
  return 0;
}

} // namespace aoc2018
