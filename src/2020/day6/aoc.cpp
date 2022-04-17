#include "aoc.h"
#include <algorithm>
#include <vector>

namespace aoc2020 {

int day6(line_view file) {
  std::vector<question_group> gs;

  const char* p1 = file.line;
  const char* p = p1;
  while (p < file.line + file.length) {
    if (*p == '\n' && *(p + 1) == '\n') {
      gs.emplace_back(line_view{p1, p});
      p1 = p + 2;
    }
    p++;
  }
  gs.emplace_back(line_view{p1, p});

  int total{0};
  std::for_each(gs.begin(), gs.end(), [&total](const question_group& g) { total += g.summary(); });
  return total;
}

} // namespace aoc2020
