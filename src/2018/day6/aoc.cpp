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
    maxy = std::max(maxy, c.y);
    return true;
  });

  std::sort(cs.begin(), cs.end());
  space_board b{maxx + 1, maxy + 1};
  printf("%d\n", b.size());

  for (size_t i = 0; i < cs.size(); i++) {
    coordinate& c = cs[i];

    auto& p = b.ps[c.y * b.rows + c.x];
    p.id = i;
    p.distance = 0;

    std::vector<int> total(1, 0);
    int win{1};

    auto f = [&win, &total, &b, &c, &i](size_t lap, coordinate x) {
      if (lap == total.size()) {
        // printf("%zu, %d %d\n", lap - 1, total[lap - 1], win);
        total.push_back(0);
      }
      if (x.x >= 0 && x.x < b.cols && x.y >= 0 && x.y < b.rows) {
        auto& p = b.ps[x.y * b.rows + x.x];
        int d = x.distance(c);
        if (d == p.distance) {
          p.id = -2; // same distance
          total[lap] += 1;
        }
        if (d < p.distance) {
          p.id = i;
          p.distance = d;
          total[lap] += 1;
          win += 1;
        }
      }
      return true;
    };
    auto g = [&total]() {
      int last = total.size() - 1;
      return total[last] == 0;
    };
    c.traverse(f, g);
    printf("%zu %d\n", i, win);
  }

  std::vector<int> xs(cs.size(), 0);
  b.count(xs);

  std::for_each(xs.begin(), xs.end(), [](int d) { printf("%d ", d); });
  printf("\n");

  int max{INT32_MIN};
  for (auto& x : xs) {
    if (x != INT32_MAX && x > max) {
      max = x;
    }
  }
  return max;
}

} // namespace aoc2018
