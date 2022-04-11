#include "aoc.h"
#include <vector>

namespace aoc2019 {

int get_number(const char** pp) {
  const char* p = *pp;
  int d{0};
  while (*p >= '0' && *p <= '9') {
    d = d * 10 + *p - '0';
    p++;
  }
  *pp = p;
  return d;
}

static void run(size_t i, std::vector<int>& codes) {
  // printf("execute %d at %zu\n", codes[i], i);
  switch (codes[i]) {
  case 1:
    codes[codes[i + 3]] = codes[codes[i + 1]] + codes[codes[i + 2]];
    run(i + 4, codes);
    break;
  case 2:
    codes[codes[i + 3]] = codes[codes[i + 1]] * codes[codes[i + 2]];
    run(i + 4, codes);
    break;
  case 99:
    break;
  default:
    printf("UNKNOWN CODE %d at %zu\n", codes[i], i);
    break;
  }
}

int test(int n, int v, std::vector<int> codes) {
  codes[1] = n;
  codes[2] = v;
  run(0, codes);
  return codes[0];
}

int test(int target, const std::vector<int>& codes) {
  for (int n = 0; n <= 99; n++) {
    for (int v = 0; v <= 99; v++) {
      if (target == test(n, v, codes)) {
        return n * 100 + v;
      }
    }
  }
  return 0;
}

std::pair<int, int> day2(line_view file) {
  std::vector<int> optcodes;
  const char* p = file.line;
  while (p < file.line + file.length) {
    if (*p >= '0' && *p <= '9') {
      optcodes.emplace_back(get_number(&p));
    }
    p++;
  }
  return {test(12, 2, optcodes), test(19690720, optcodes)};
}

} // namespace aoc2019
