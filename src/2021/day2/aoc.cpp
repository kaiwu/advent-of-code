#include "aoc.h"

namespace aoc2021 {

std::pair<int, int> day2(line_view file) {
  meters m1{0, 0};
  meters m2{0, 0};
  int aim;
  per_line(file, [&m1, &m2, &aim](line_view lv) {
    m1.apply(lv);
    m2.apply(lv, &aim);
    return true;
  });
  return {m1.depth * m1.horizontal, m2.depth * m2.horizontal};
}

} // namespace aoc2021
