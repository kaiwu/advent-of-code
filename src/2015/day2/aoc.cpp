#include "aoc.h"

namespace aoc2015 {

int cal_day2(const char* p1, const char* p2) {
  int x = 0;
  const char* p = p1;
  while (p != p2) {
    x = x * 10 + (*p) - '0';
    p++;
  }
  return x;
}

/*
27x2x5
29x13x26
*/
box parse_day2(line_view lv) {
  box b;
  int* is[] = {&b.l, &b.w, &b.h};
  const char* p1 = lv.line;
  const char* p2 = p1;
  const char* pe = p1 + lv.length;
  int i = 0;
  while (p2 != pe) {
    if ((*p2) >= '0' && (*p2) <= '9') {
      p2++;
    } else {
      *is[i++] = cal_day2(p1, p2);
      p1 = p2 + 1;
      p2 = p1;
    }
  }
  return b;
}

inline int min_square(box b) {
  int x1 = b.l * b.w;
  int x2 = b.l * b.h;
  int x3 = b.h * b.w;
  return std::min(std::min(x1, x2), x3);
}

inline int min_perimeter(box b) {
  int x1 = b.l + b.w;
  int x2 = b.l + b.h;
  int x3 = b.h + b.w;
  return 2 * std::min(std::min(x1, x2), x3);
}

inline int surface(box b) { return 2 * b.l * b.w + 2 * b.l * b.h + 2 * b.w * b.h; }
inline int squire(box b) { return b.l * b.w * b.h; }

std::pair<int, int> day2(line_view input) {
  int total = 0;
  int ribbon = 0;
  per_line(input, [&total, &ribbon](line_view line) {
    box b = parse_day2(line);
    total += surface(b) + min_square(b);
    ribbon += squire(b) + min_perimeter(b);
    return true;
  });
  return {total, ribbon};
}

} // namespace aoc2015
