#pragma once
#include "common.h"
#include <map>
#include <set>

namespace aoc2018 {

struct instruction {
  static std::map<char, instruction*> instructions;
  static size_t done_total;

  static bool all_done() { return done_total >= instructions.size(); }

  static instruction* make(char x) {
    auto it = instructions.find(x);
    if (it == instructions.end()) {
      auto p = instructions.insert({x, new instruction{x, false, INT32_MAX, {}}});
      return p.first->second;
    }
    return it->second;
  }

  static void undo() {
    for (auto& kv : instructions) {
      kv.second->done = false;
    }
    done_total = 0;
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

  static void next(instruction** n) {
    for (auto& kv : instructions) {
      if (kv.second->ready() && kv.second->start == INT32_MAX) {
        *n = kv.second;
        return;
      }
    }
    *n = nullptr;
  }

  char label;
  bool done;
  int start;
  std::set<instruction*> deps;

  void add_dependency(instruction* x) noexcept { deps.insert(x); }
  void make_done() noexcept {
    done = true;
    done_total += 1;
  }
  void begin(int s) noexcept { start = s; }
  bool operator<(const instruction& other) const noexcept { return label < other.label; }

  bool ready(const std::set<instruction*> ds) const noexcept {
    for (auto& i : ds) {
      if (!i->done) {
        return false;
      }
    }
    return true;
  }

  bool finished(int s) const noexcept { return start != INT32_MAX && s >= start + label - 'A' + 1 + 60; }
  bool ready() const noexcept { return !done && (deps.empty() || ready(deps)); }
};

int day7(line_view, char[]);

} // namespace aoc2018
