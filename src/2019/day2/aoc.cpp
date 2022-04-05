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

void run(size_t i, std::vector<int>& codes) {
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

int day2(line_view file) {
  std::vector<int> optcodes;
  const char* p = file.line;
  while (p < file.line + file.length) {
    if (*p >= '0' && *p <= '9') {
      optcodes.emplace_back(get_number(&p));
    }
    p++;
  }
  optcodes[1] = 12;
  optcodes[2] = 2;
  run(0, optcodes);
  return optcodes[0];
}

} // namespace aoc2019
