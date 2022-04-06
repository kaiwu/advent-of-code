#include "aoc.h"

namespace aoc2018 {

int day3(line_view file, int x) {
  fabric* f = new fabric;
  per_line(file, [&f](line_view lv) {
    f->parse(lv);
    return true;
  });

  return f->count(x);
}

} // namespace aoc2018
