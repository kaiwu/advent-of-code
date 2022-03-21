#include "aoc.h"

namespace aoc2015 {

std::pair<size_t,size_t> day17(line_view file, int t) {
  kichen ki;
  per_line(file, [&ki](line_view lv) {
    ki.parse(lv);
    return true;
  });
  std::vector<int> c(ki.containers.size(),0);
  std::vector<std::vector<int>> combo;
  // std::for_each(ki.containers.begin(), ki.containers.end(), [](int i) { printf("%d\n", i); });
  ki.fill(t, 0, c, combo);
  return {combo.size(), ki.min(combo)};
}

} // namespace aoc2015
