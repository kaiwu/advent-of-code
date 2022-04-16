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

    auto f = [&total, &b, &c, &i](size_t lap, coordinate x) {
      if (x.x >= 0 && x.x <= b.cols && x.y >= 0 && x.y <= b.rows) {
        if (lap == total.size()) {
          total.push_back(0);
        }
        auto& p = b.ps[x.y * b.rows + x.x];
        int d = x.distance(c);
        if (d < p.distance) {
          p.id = i;
          p.distance = d;
          total[lap] += 1;
        }
        if (d == p.distance) {
          p.id = -2; // same distance
          total[lap] += 1;
        }
      }
      return true;
    };
    auto g = [&total]() { return total[total.size() - 1] == 0; };
    c.traverse(f, g);
  }

  std::vector<int> xs(cs.size(), 0);
  b.count(xs);

  int max{INT32_MIN};
  for (auto& x : xs) {
    if (x != INT32_MAX && x > max) {
      max = x;
    }
  }
  return max;
}

} // namespace aoc2018
