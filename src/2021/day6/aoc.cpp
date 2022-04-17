#include "aoc.h"
#include <algorithm>
#include <vector>

namespace aoc2021 {

static void run(int day, std::vector<int>& v) {
  // std::for_each(v.begin(), v.end(), [](int i) { printf("%d ", i); });
  // printf(": %zu\n", v.size());
  if (day > 0) {
    int count{0};
    for (auto& i : v) {
      if (i > 0) {
        i--;
      } else {
        i = 6;
        count += 1;
      }
    }
    while (count > 0) {
      v.push_back(8);
      count--;
    }
    run(day - 1, v);
  }
}

size_t day6(int i, int days) {
  std::vector<int> v = {i};
  run(days, v);
  return v.size();
}

size_t day6(line_view file, int days) {
  size_t ns[7] = {0};
  for (int i : {0, 1, 2, 3, 4, 5, 6}) {
    ns[i] = day6(i, days);
    printf("--> %d : %zu\n", i, ns[i]);
  }

  size_t total{0};
  const char* p = file.line;
  while (p < file.line + file.length) {
    if (*p >= '0' && *p <= '9') {
      total += ns[*p - '0'];
    }
    p++;
  }
  return total;
}

} // namespace aoc2021
