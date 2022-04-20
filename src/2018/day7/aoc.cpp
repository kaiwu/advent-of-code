#include "aoc.h"

namespace aoc2018 {
std::map<char, instruction*> instruction::instructions = {};
size_t instruction::done_total = 0;

int day7(line_view file, char sequence[]) {
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

  auto check = [](int s, instruction** w) {
    if (*w != nullptr && (*w)->finished(s)) {
      (*w)->make_done();
      // std::cout << (*w)->label << " finishes at " << s << std::endl;
      *w = nullptr;
    }

    if (*w == nullptr) {
      instruction::next(w);
      if (*w != nullptr) {
        // std::cout << (*w)->label << " starts at " << s << std::endl;
        (*w)->begin(s);
      }
    }
  };

  instruction::undo();
  int second{0};
  instruction* workers[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
  // instruction* workers[2] = {nullptr, nullptr};
  bool stop{false};
  while (!stop) {
    for (size_t i = 0; i < ARRAY_SIZE(workers) && !stop; i++) {
      check(second, &workers[i]);
    }
    stop = instruction::all_done();
    second += int(!stop);
  }
  return second;
}

} // namespace aoc2018
