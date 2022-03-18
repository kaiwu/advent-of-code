#include "aoc.h"

namespace aoc2015 {
// a -> 1
// \\ -> 1
// \" -> 1
// \xXX -> 1
std::pair<int, int> count_day8(line_view lv) {
  int t1 = 0;
  int t2 = 0;
  const char* p1 = lv.line;
  const char* p2 = lv.line + lv.length;
  const char* p = p1;
  while (p != p2) {
    if (*p != '\\' || p == p2 - 1) {
      t1 += 1;
      t2 += 1;
      p++;
      continue;
    } else {
      if (*(p + 1) == '\\' || *(p + 1) == '"') {
        t1 += 1;
        t2 += 4;
        p += 2;
        continue;
      }
      if (*(p + 1) == 'x') {
        t1 += 1;
        t2 += 5;
        p += 4;
        continue;
      }
      t1 += 1;
      t2 += 1;
      p++;
    }
  }
  return {t1, t2};
}

std::pair<int, int> day8(line_view file) {
  int t1 = 0;
  int t2 = 0;
  int t3 = 0;
  per_line(file, [&t1, &t2, &t3](line_view lv) {
    t1 += lv.length - 1;
    auto p = count_day8({lv.line + 1, lv.line + lv.length - 2});
    t2 += p.first;
    t3 += p.second + 6;
    return true;
  });
  return {t1 - t2, t3 - t1};
}

} // namespace aoc2015
