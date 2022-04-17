#pragma once
#include "common.h"
#include <vector>

namespace aoc2020 {

struct question_group {
  line_view people;
  int count[26] = {0};

  int summary() const noexcept {
    int total{0};
    for (int x : count) {
      total += int(x > 0);
    }
    return total;
  }

  int common(const std::vector<line_view>& vs) const noexcept {
    line_view shortest{nullptr, INT32_MAX};
    for (auto& l : vs) {
      if (l.length < shortest.length) {
        shortest = l;
      }
    }

    std::vector<int> ts(shortest.length, 0);
    int i{0};
    per_char(shortest, [&vs, &ts, &i](char c) {
      char t[2] = {c, '\0'};
      for (auto& l : vs) {
        const char* p = l.contains(line_view{t, 1});
        ts[i] += int(p != nullptr);
      }
      i++;
      return true;
    });

    int total{0};
    for (auto i : ts) {
      total += int(!(size_t(i) < vs.size()));
    }
    return total;
  }

  int common() const noexcept {
    std::vector<line_view> ls;
    const char* p1 = people.line;
    const char* p = p1;
    while (p < people.line + people.length) {
      if (*p == '\n') {
        ls.emplace_back(p1, p);
        p1 = p + 1;
      }
      p++;
    }
    return common(ls);
  }

  question_group(line_view lv) : people(lv) {
    const char* p = lv.line;
    while (p < lv.line + lv.length) {
      if (*p >= 'a' && *p <= 'z') {
        count[*p - 'a'] += 1;
      }
      p++;
    }
  }
};

std::pair<int, int> day6(line_view);

} // namespace aoc2020
