#include "aoc.h"
#include <algorithm>

namespace aoc2021 {

static void get_length(const char** pp, int* d) {
  const char* p = *pp;
  *d = 0;
  while (*p >= 'a' && *p <= 'g') {
    *d += 1;
    p++;
  }
  *pp = p;
}

int day8(line_view file) {
  // int digits[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
  int total{0};
  int ls[4] = {0};
  per_line(file, [&ls, &total](line_view lv) {
    const char* p = lv.contains("|") + 2;
    int index{0};
    while (p < lv.line + lv.length) {
      get_length(&p, &ls[index]);
      total += int(ls[index] == 2 || ls[index] == 3 || ls[index] == 4 || ls[index] == 7);
      index++;
      p++;
    }
    return true;
  });
  return total;
}

} // namespace aoc2021
