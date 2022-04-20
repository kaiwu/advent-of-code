#include "aoc.h"
#include <algorithm>

namespace aoc2018 {
std::map<char, instruction*> instruction::instructions = {};
size_t instruction::done_total = 0;

void print() {
  for (auto& kv : instruction::instructions) {
    std::cout << kv.second->label << " -> ";
    for (auto x : kv.second->deps) {
      std::cout << x->label << " ";
    }
    std::cout << std::endl;
  }
}

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

  // print();

  auto check = [](int s, instruction** w, size_t size) {
    for (size_t i = 0; i < size; i++) {
      if (w[i] != nullptr && w[i]->finished(s)) {
        (w[i])->make_done();
        w[i] = nullptr;
      }
    }

    for (size_t i = 0; i < size; i++) {
      if (w[i] == nullptr) {
        instruction::next(&w[i]);
        if (w[i] != nullptr) {
          w[i]->begin(s);
        }
      }
    }
  };

  instruction::undo();
  int second{0};
  instruction* workers[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
  // instruction* workers[2] = {nullptr, nullptr};
  bool stop{false};
  while (!stop) {
    check(second, workers, ARRAY_SIZE(workers));
    stop = instruction::all_done();
    second += int(!stop);
  }
  return second;
}

} // namespace aoc2018
