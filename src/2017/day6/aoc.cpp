#include "aoc.h"
#include <set>

namespace aoc2017 {

void next(int* step, memory_bank& m, std::set<memory_bank>& ms) {
  if (ms.find(m) == ms.end()) {
    ms.insert(m);
    *step += 1;
    int d{0};
    int i = m.highest(&d);
    // printf("%d %d %d\n", *step, i, d);
    m.distribute(i, d);
    next(step, m, ms);
  }
}

int day6(line_view file) {
  std::set<memory_bank> ms;
  memory_bank m{file};
  int steps{0};
  next(&steps, m, ms);
  return steps;
}

} // namespace aoc2017
