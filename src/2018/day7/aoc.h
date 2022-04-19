#pragma once
#include "common.h"
#include <map>
#include <set>

namespace aoc2018 {

struct instruction {
  static std::map<char, instruction*> instructions;

  static instruction* make(char x) {
    auto it = instructions.find(x);
    if (it == instructions.end()) {
      auto p = instructions.insert({x, new instruction{x, false, {}}});
      return p.first->second;
    }
    return it->second;
  }

  static instruction* next() {
    instruction* n = nullptr;
    for (auto& kv : instructions) {
      if (kv.second->ready()) {
        if (n == nullptr) {
          n = kv.second;
        } else {
          if (*kv.second < *n) {
            n = kv.second;
          }
        }
      }
    }
    return n; // if nullptr all done
  }

  char label;
  bool done;
  std::set<instruction*> deps;

  void add_dependency(instruction* x) noexcept { deps.insert(x); }
  void make_done() noexcept { done = true; }
  bool operator<(const instruction& other) const noexcept { return label < other.label; }

  bool ready(const std::set<instruction*> ds) const noexcept {
    for (auto& i : ds) {
      if (!i->done) {
        return false;
      }
    }
    return true;
  }

  bool ready() const noexcept { return !done && (deps.empty() || ready(deps)); }
};

void day7(line_view, char[]);

} // namespace aoc2018
