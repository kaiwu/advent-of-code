#include "aoc.h"

namespace aoc2016 {

int day2(line_view file, char ds[]) {
  int d{0};
  size_t i{0};
  char l{5};
  keybad pad;
  per_line(file, [&d, &l, &pad, &i, &ds](line_view lv) {
    l = pad.touch(l, lv.line, pad.digit_keys);
    // printf("%d\n", l);
    d = d * 10 + l;
    pad.touch(i++, ds, lv.line, pad.diamond_keys);
    return true;
  });
  return d;
}

} // namespace aoc2016
