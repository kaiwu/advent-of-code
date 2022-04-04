#include "aoc.h"

namespace aoc2016 {

int day2(line_view file) {
  int d{0};
  int l{5};
  keybad pad;
  per_line(file, [&d, &l, &pad](line_view lv) {
    l = pad.touch(l, lv.line);
    // printf("%d\n", l);
    d = d * 10 + l;
    return true;
  });
  return d;
}

} // namespace aoc2016
