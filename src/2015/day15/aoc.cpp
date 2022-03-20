#include "aoc.h"

namespace aoc2015 {

int day15(line_view file) {
  recipe r;
  per_line(file, [&r](line_view lv) {
    r.parse(lv);
    return true;
  });

  std::vector<int> combos;
  int best{0};
  r.measure(100, 0, combos, &best);
  return best;
}
} // namespace aoc2015
