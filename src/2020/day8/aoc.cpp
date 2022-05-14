#include "aoc.h"
#include <vector>

namespace aoc2020 {

static void run(size_t index, std::vector<code>& cs, int* accumlator) {
  auto& code = cs[index];
  if (code.executed == 0) {
    size_t next = index + 1;
    if (code.type == acc) {
      *accumlator += code.value;
    }
    if (code.type == jmp) {
      next = index + code.value;
    }
    code.executed += 1;
    run(next, cs, accumlator);
  }
}

int day8(line_view file) {
  std::vector<code> cs;
  int accumlator = 0;
  per_line(file, [&cs](line_view lv) {
    cs.emplace_back(lv);
    return true;
  });

  run(0, cs, &accumlator);
  return accumlator;
}

} // namespace aoc2020
