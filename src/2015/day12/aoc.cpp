#include "aoc.h"

namespace aoc2015 {

int parse_day12(const char* p1, const char* p2) {
  int sign = *(p1 - 1) == '-' ? -1 : 1;
  int d{0};
  while (p1 != p2) {
    d = d * 10 + *p1 - '0';
    p1++;
  }
  return sign * d;
}

int day12(line_view file) {
  int total = 0;
  const char* p1 = file.line;
  const char* p2 = p1;
  bool to_parse = false;
  while (p2 < file.line + file.length) {
    if (*p2 >= '0' && *p2 <= '9') {
      if (!to_parse) {
        p1 = p2;
        to_parse = !to_parse;
      }
    } else {
      if (to_parse) {
        total += parse_day12(p1, p2);
        to_parse = !to_parse;
      }
    }
    p2++;
  }
  if (to_parse) {
    total += parse_day12(p1, p2);
  }
  return total;
}

} // namespace aoc2015
