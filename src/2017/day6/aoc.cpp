#include "aoc.h"
#include <set>

namespace aoc2017 {

void next(int* step, int* gap, memory_bank& m, std::set<memory_bank>& ms) {
  if (ms.find(m) == ms.end()) {
    ms.insert(m);
    *step += 1;
    int d{0};
    int i = m.highest(&d);
    // printf("%d %d %d\n", *step, i, d);
    m.distribute(i, d);
    next(step, gap, m, ms);
  }
  auto it = ms.find(m);
  *gap = *step - it->index;
}

std::pair<int, int> day6(line_view file) {
  std::set<memory_bank> ms;
  memory_bank m{file};
  int steps{0};
  int gap{0};
  next(&steps, &gap, m, ms);
  return {steps, gap};
}

} // namespace aoc2017
