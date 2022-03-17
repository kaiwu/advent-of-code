#include "aoc.h"

namespace aoc2015 {

result day7(line_view file, const char* wire) {
  cals cs;
  per_line(file, [&cs](line_view lv) {
    cs.parse(lv);
    return true;
  });
  return cs.compute(wire);
}

} // namespace aoc2015
