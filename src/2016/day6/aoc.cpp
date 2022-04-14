#include "aoc.h"

namespace aoc2016 {

struct counter {
  int az[26] = {0};

  void add(char c) { az[c - 'a'] += 1; }
  char most() {
    int max{INT32_MIN};
    int index{0};
    for (int i = 0; i < 26; i++) {
      if (az[i] > max) {
        max = az[i];
        index = i;
      }
    }
    return 'a' + index;
  }
};

void day6(line_view file, char msg[]) {
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
    msg[i] = cs[i].most();
  }
}

} // namespace aoc2016
