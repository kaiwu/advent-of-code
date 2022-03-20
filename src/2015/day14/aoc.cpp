#include "aoc.h"
namespace aoc2015 {
int day14(line_view file, int seconds) {
  olympics games;
  per_line(file, [&games](line_view lv) {
    games.parse(lv);
    return true;
  });
  auto p = games.best(seconds);
  return p.second;
}

} // namespace aoc2015
