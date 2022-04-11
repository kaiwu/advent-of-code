#include "aoc.h"
#include <vector>

namespace aoc2019 {

static int input = 1;
static std::vector<int> outputs = {};

void get_number(const char** pp, int* d) {
  const char* p = *pp;
  int sign = 1;
  if (*p == '-') {
    sign = -1;
    p++;
  }
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *d *= sign;
  *pp = p;
}

static void run(size_t i, std::vector<int>& codes) {
  // printf("execute %d at %zu\n", codes[i], i);
  switch (codes[i]) {
  case 1:
    codes[codes[i + 3]] = codes[codes[i + 1]] + codes[codes[i + 2]];
    run(i + 4, codes);
    break;
  case 101:
    codes[codes[i + 3]] = codes[i + 1] + codes[codes[i + 2]];
    run(i + 4, codes);
    break;
  case 1001:
    codes[codes[i + 3]] = codes[codes[i + 1]] + codes[i + 2];
    run(i + 4, codes);
    break;
  case 1101:
    codes[codes[i + 3]] = codes[i + 1] + codes[i + 2];
    run(i + 4, codes);
    break;
  case 2:
    codes[codes[i + 3]] = codes[codes[i + 1]] * codes[codes[i + 2]];
    run(i + 4, codes);
    break;
  case 102:
    codes[codes[i + 3]] = codes[i + 1] * codes[codes[i + 2]];
    run(i + 4, codes);
    break;
  case 1002:
    codes[codes[i + 3]] = codes[codes[i + 1]] * codes[i + 2];
    run(i + 4, codes);
    break;
  case 1102:
    codes[codes[i + 3]] = codes[i + 1] * codes[i + 2];
    run(i + 4, codes);
    break;
  case 3:
    codes[codes[i + 1]] = input;
    run(i + 2, codes);
    break;
  case 4:
    // printf("%d\n", codes[codes[i + 1]]);
    outputs.push_back(codes[codes[i + 1]]);
    run(i + 2, codes);
    break;
  case 104:
    // printf("%d\n", codes[i + 1]);
    outputs.push_back(codes[i + 1]);
    run(i + 2, codes);
    break;
  case 99:
    break;
  default:
    printf("UNKNOWN CODE %d at %zu\n", codes[i], i);
    break;
  }
}

int day5(line_view file) {
  const char* p = file.line;
  std::vector<int> optcodes;
  while (p < file.line + file.length) {
    if ((*p >= '0' && *p <= '9') || *p == '-') {
      int d{0};
      get_number(&p, &d);
      optcodes.push_back(d);
    }
    p++;
  }
  input = 1;
  run(0, optcodes);
  return outputs[outputs.size() - 1];
}

} // namespace aoc2019
