#pragma once

#include "common.h"
#include <algorithm>
#include <stack>
#include <vector>

namespace aoc2015 {

struct kichen {
  std::vector<int> containers;

  int get_number(const char* p) {
    int d{0};
    while ((*p) >= '0' && (*p) <= '9') {
      d = d * 10 + *p - '0';
      p++;
    }
    return d;
  }

  int count(const std::vector<int>& is) {
    int d{0};
    for (auto i : is) {
      if (i > 0) {
        d++;
      }
    }
    return d;
  }

  void fill(int total, size_t index, std::vector<int>& c, std::vector<std::vector<int>>& combos) {
    if (0 == total) {
      // std::for_each(c.begin(), c.end(), [](int i) { printf("%02d ", i); });
      // printf("\n");
      combos.push_back(c);
      return;
    }
    if (index < containers.size()) {
      // printf("--> %d [%zu]%d?\n", total, index, containers[index]);
      if (containers[index] > total) {
        c[index] = 0;
        fill(total, index + 1, c, combos);
      } else {
        for (int i = 0; i < 2; i++) {
          int x = i == 0 ? containers[index] : 0;
          c[index] = x;
          fill(total - x, index + 1, c, combos);
        }
      }
    }
  }

  size_t min(const std::vector<std::vector<int>>& combos) {
    std::stack<int> is;
    for (auto& c : combos) {
      int x = count(c);
      if (is.empty() || x == is.top()) {
        is.push(x);
      } else if (x < is.top()) {
        while (!is.empty()) {
          is.pop();
        }
        is.push(x);
      }
    }
    return is.size();
  }

  void parse(line_view lv) { containers.push_back(get_number(lv.line)); }
};

std::pair<size_t, size_t> day17(line_view, int);

} // namespace aoc2015
