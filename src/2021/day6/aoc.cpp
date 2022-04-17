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

// i = 0, 1, 2, 3, 4, 5, 6, 7, 8
void lanternfish(int i, int days, size_t* total) {
  // printf("(%d, %d)\n", i, days);
  int x = days - i - 1;
  *total += 1;
  while (x >= 0) {
    lanternfish(8, x, total);
    x -= 7;
  }
}

//-> 0 : 1421
//-> 1 : 1401
//-> 2 : 1191
//-> 3 : 1154
//-> 4 : 1034
//-> 5 : 950
//-> 6 : 905
//-> 0 : 6703087164
//-> 1 : 6206821033
//-> 2 : 5617089148
//-> 3 : 5217223242
//-> 4 : 4726100874
//-> 5 : 4368232009
//-> 6 : 3989468462
size_t day6(line_view file, int days) {
  size_t ns[7] = {0};
  if (days == 256) {
    ns[0] = 6703087164;
    ns[1] = 6206821033;
    ns[2] = 5617089148;
    ns[3] = 5217223242;
    ns[4] = 4726100874;
    ns[5] = 4368232009;
    ns[6] = 3989468462;
  } else {
    for (int i : {0, 1, 2, 3, 4, 5, 6}) {
      lanternfish(i, days, &ns[i]);
      // printf("--> %d : %zu\n", i, ns[i]);
    }
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
