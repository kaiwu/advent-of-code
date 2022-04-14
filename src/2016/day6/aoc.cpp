#include "aoc.h"

namespace aoc2016 {

struct counter {
  int az[26] = {0};

  void add(char c) { az[c - 'a'] += 1; }
  std::pair<char, char> minmax() const noexcept {
    int max{INT32_MIN};
    int min{INT32_MAX};
    int i1{0};
    int i2{0};
    for (int i = 0; i < 26; i++) {
      if (az[i] > 0 && az[i] > max) {
        max = az[i];
        i1 = i;
      }
      if (az[i] > 0 && az[i] < min) {
        min = az[i];
        i2 = i;
      }
    }
    return {'a' + i1, 'a' + i2};
  }
};

void day6(line_view file, char msg1[], char msg2[]) {
  counter cs[8];
  per_line(file, [&cs](line_view lv) {
    const char* p = lv.line;
    int index{0};
    while (p < lv.line + lv.length) {
      if (*p >= 'a' && *p <= 'z') {
        cs[index++].add(*p);
      }
      p++;
    }
    return true;
  });

  for (size_t i = 0; i < ARRAY_SIZE(cs); i++) {
    auto p = cs[i].minmax();
    msg1[i] = p.first;
    msg2[i] = p.second;
  }
}

} // namespace aoc2016
