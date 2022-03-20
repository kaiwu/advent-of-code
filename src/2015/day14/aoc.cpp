#include "aoc.h"
namespace aoc2015 {
std::pair<int, int> day14(line_view file, int seconds) {
  olympics games;
  per_line(file, [&games](line_view lv) {
    games.parse(lv);
    return true;
  });
  auto p1 = games.best(seconds);
  auto p2 = games.best_points(seconds);
  return {p1.second, p2.second};
}

} // namespace aoc2015
