#include "aoc.h"

namespace aoc2018 {
std::map<char, instruction*> instruction::instructions = {};

void day7(line_view file, char sequence[]) {
  per_line(file, [](line_view lv) {
    char p1 = *(lv.line + 5);
    char p2 = *(lv.line + 36);
    instruction* i1 = instruction::make(p1);
    instruction* i2 = instruction::make(p2);
    i2->add_dependency(i1);
    return true;
  });

  instruction* n = instruction::next();
  int i{0};
  while (n != nullptr) {
    sequence[i++] = n->label;
    n->make_done();
    n = instruction::next();
  }
}

} // namespace aoc2018
