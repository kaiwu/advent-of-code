#include "aoc.h"
#include <algorithm>
#include <vector>

namespace aoc2020 {

std::pair<int, int> day6(line_view file) {
  std::vector<question_group> gs;

  const char* p1 = file.line;
  const char* p = p1;
  while (p < file.line + file.length) {
    if (*p == '\n' && *(p + 1) == '\n') {
      gs.emplace_back(line_view{p1, p + 1});
      p1 = p + 2;
    }
    p++;
  }
  gs.emplace_back(line_view{p1, p});

  int t0{0};
  int t1{0};
  std::for_each(gs.begin(), gs.end(), [&t0, &t1](const question_group& g) {
    t0 += g.summary();
    t1 += g.common();
  });
  return {t0, t1};
}

} // namespace aoc2020
