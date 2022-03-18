#include "aoc.h"

namespace aoc2015 {

result day7(line_view file, const char* wire, const char* extra) {
  cals cs;
  per_line(file, [&cs](line_view lv) {
    cs.parse({lv.line, lv.line + lv.length - 1});
    return true;
  });
  if (extra != nullptr) {
    cs.parse(extra);
  }
  return cs.compute(wire);
}

} // namespace aoc2015
