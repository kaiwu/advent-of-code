#include "aoc.h"
#include <set>
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

int two_sum(const std::vector<int>& is, int target) {
  std::set<int> pairs;
  for (auto i : is) {
    auto it = pairs.find(i);
    if (it == pairs.end()) {
      pairs.insert(target - i);
    } else {
      return i * (target - *it);
    }
  };
  return 0;
}

int three_sum(const std::vector<int>& is, int target) { return 0; }

std::pair<int, int> day1(line_view file, int target) {
  std::vector<int> is;
  per_line(file, [&is](line_view lv) {
    is.emplace_back(get_number(lv.line));
    return true;
  });
  return {two_sum(is, target), three_sum(is, target)};
}

} // namespace aoc2020
