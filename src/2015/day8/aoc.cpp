#include "aoc.h"

namespace aoc2015 {
// a -> 1
// \\ -> 1
// \" -> 1
// \xXX -> 1
int count_day8(line_view lv) {
  int total = 0;
  const char* p1 = lv.line;
  const char* p2 = lv.line + lv.length;
  const char* p = p1;
  while (p != p2) {
    if (*p != '\\' || p == p2 - 1) {
      total += 1;
      p++;
      continue;
    } else {
      if (*(p + 1) == '\\' || *(p + 1) == '"') {
        total += 1;
        p += 2;
        continue;
      }
      if (*(p + 1) == 'x') {
        total += 1;
        p += 4;
        continue;
      }
      total += 1;
      p++;
    }
  }
  return total;
}

int day8(line_view file) {
  int t1 = 0;
  int t2 = 0;
  per_line(file, [&t1, &t2](line_view lv) {
    t1 += lv.length - 1;
    t2 += count_day8({lv.line + 1, lv.line + lv.length - 2});
    return true;
  });
  return t1 - t2;
}

} // namespace aoc2015
