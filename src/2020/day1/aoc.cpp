#include "aoc.h"
#include <set>
#include <utility>
#include <vector>

namespace aoc2020 {

int get_number(const char* p) {
  int d{0};
  while (*p >= '0' && *p <= '9') {
    d = d * 10 + *p - '0';
    p++;
  }
  return d;
}

int two_sum(int* is, size_t s, int target) {
  std::set<int> pairs;
  for (size_t i = 0; i < s; i++) {
    auto it = pairs.find(is[i]);
    if (it == pairs.end()) {
      pairs.insert(target - is[i]);
    } else {
      return is[i] * (target - *it);
    }
  };
  return 0;
}

int three_sum(std::vector<int>& is, int target) {
  for (size_t i = 0; i < is.size(); i++) {
    std::swap(is[0], is[i]);
    int x = two_sum(&is[1], is.size() - 1, target - is[0]);
    if (x > 0) {
      return is[0] * x;
    }
  }
  return 0;
}

std::pair<int, int> day1(line_view file, int target) {
  std::vector<int> is;
  per_line(file, [&is](line_view lv) {
    is.emplace_back(get_number(lv.line));
    return true;
  });
  return {two_sum(is.data(), is.size(), target), three_sum(is, target)};
}

} // namespace aoc2020
