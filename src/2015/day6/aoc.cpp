#include "aoc.h"

namespace aoc2015 {
std::pair<int, int> day6(line_view file) {
  grid<Bit, 1000>* grid1 = new grid<Bit,1000>;
  grid<int8_t, 1000>* grid2 = new grid<int8_t, 1000>;
  per_line(file, [&grid1, &grid2](line_view lv) {
    grid1->parse(lv);
    grid2->parse(lv);
    return true;
  });
  return {grid1->store_.count(), grid2->store_.count()};
}
} // namespace aoc2015
