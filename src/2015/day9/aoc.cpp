#include "aoc.h"

namespace aoc2015 {
std::pair<int, int> day9(line_view file) {
  world_day9 world;
  per_line(file, [&world](line_view lv) {
    world.parse(lv);
    return true;
  });
  std::pair<int, int> d{INT32_MAX, INT32_MIN};
  for (auto city : world.locations) {
    auto p = world.plan(city);
    if (p.first < d.first) {
      d.first = p.first;
    }
    if (p.second > d.second) {
      d.second = p.second;
    }
  }
  return d;
}

} // namespace aoc2015
