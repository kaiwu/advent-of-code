#include "aoc.h"

namespace aoc2015 {
int day6(line_view file) {
  grid<1000> grid;
  per_line(file, [&grid](line_view lv) {
    grid.parse(lv);
    return true;
  });
  return grid.count();
}
} // namespace aoc2015
