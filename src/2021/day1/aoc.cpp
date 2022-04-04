#include "aoc.h"
#include <algorithm>
#include <vector>

namespace aoc2021 {

int get_number(const char* p) {
  int d{0};
  while (*p >= '0' && *p <= '9') {
    d = d * 10 + *p - '0';
    p++;
  }
  return d;
}

int increase_1(const std::vector<int>& is) {
  int total{0};
  int last{0};
  std::for_each(is.begin(), is.end(), [&total, &last](int d) {
    total += (last != 0 && d > last) ? 1 : 0;
    last = d;
    return true;
  });
  return total;
}

int increase_3(const std::vector<int>& is) {
  int total{0};
  auto sum3 = [](const int* is) { return *is + *(is + 1) + *(is + 2); };
  const int* p1 = is.data();
  const int* p2 = p1 + is.size() - 3;
  while (p1 < p2) {
    if (sum3(p1 + 1) > sum3(p1)) {
      total += 1;
    }
    p1++;
  }
  return total;
}

std::pair<int, int> day1(line_view file) {
  std::vector<int> is;
  per_line(file, [&is](line_view lv) {
    is.emplace_back(get_number(lv.line));
    return true;
  });
  return {increase_1(is), increase_3(is)};
}

} // namespace aoc2021
