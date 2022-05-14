#include "aoc.h"
#include <vector>

namespace aoc2020 {

static int run(size_t index, std::vector<code> cs, int* accumlator) {
  if (index < cs.size()) {
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
      return run(next, cs, accumlator);
    }
    return 1;
  }
  return 0;
}

std::pair<int, int> day8(line_view file) {
  std::vector<code> cs;
  int acc0 = 0;
  per_line(file, [&cs](line_view lv) {
    cs.emplace_back(lv);
    return true;
  });
  run(0, cs, &acc0);

  auto reset = [](code& c) {
    c.type = (code_t)(!(int)c.type);
  };
  int acc1 = 0;
  for(auto& code: cs) {
    if (code.type != acc) {
      reset(code);
      acc1 = 0;
      if (run(0, cs, &acc1) == 0) {
        break;
      }
      reset(code);
    }
  }
  return {acc0, acc1};
}

} // namespace aoc2020
