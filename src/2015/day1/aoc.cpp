#include "aoc.h"

namespace aoc2015 {

int day1(line_view lv) {
  int level = 0;
  for (size_t i = 0; i < lv.length; ++i) {
    level += lv.line[i] == '(' ? 1 : -1;
  }
  return level;
}

} // namespace aoc2015
