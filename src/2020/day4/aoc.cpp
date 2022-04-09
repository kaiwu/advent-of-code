#include "aoc.h"

namespace aoc2020 {

int day4(line_view file) {
  const char* p1 = file.line;
  const char* p2 = file.line + file.length;
  const char* p = p1;
  int total{0};
  while (p < p2) {
    if (*p == '\n' && *(p + 1) == '\n') {
      passwort pass{p1, p};
      // std::cout << pass << std::endl;
      if (pass.is_valid()) {
        total++;
      }
      p1 = p + 2;
    }
    p++;
  }
  if (passwort{p1, p}.is_valid()) {
    total++;
  }
  return total;
}

} // namespace aoc2020
