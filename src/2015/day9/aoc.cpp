#include "aoc.h"

namespace aoc2015 {
int day9(line_view file) {
  world_day9 world;
  per_line(file, [&world](line_view lv) {
    world.parse(lv);
    return true;
  });
  world.check();
  return 0;
}

} // namespace aoc2015
