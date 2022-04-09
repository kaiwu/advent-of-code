#include "aoc.h"

namespace aoc2020 {

std::pair<int, int> day4(line_view file) {
  const char* p1 = file.line;
  const char* p2 = file.line + file.length;
  const char* p = p1;
  int t0{0};
  int t1{0};
  bool b1{false};
  bool b2{false};
  while (p < p2) {
    if (*p == '\n' && *(p + 1) == '\n') {
      passport pass{p1, p};
      // std::cout << pass << std::endl;
      pass.is_valid(&b1, &b2);
      t0 += int(b1);
      t1 += int(b2);
      p1 = p + 2;
    }
    p++;
  }
  passport{p1, p}.is_valid(&b1, &b2);
  t0 += int(b1);
  t1 += int(b2);
  return {t0, t1};
}

} // namespace aoc2020
