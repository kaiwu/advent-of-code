#include "aoc.h"

namespace aoc2015 {

int day1(line_view lv) {
  int level = 0;
  for (size_t i = 0; i < lv.length; ++i) {
    switch (lv.line[i]) {
    case '(':
      level += 1;
      break;
    case ')':
      level += -1;
      break;
    default:
      break;
    }
  }
  return level;
}

int day1(line_view lv, int target) {
  int level = 0;
  for (size_t i = 0; i < lv.length; ++i) {
    switch (lv.line[i]) {
    case '(':
      level += 1;
      break;
    case ')':
      level += -1;
      break;
    default:
      break;
    }
    if (level == target) {
      return i + 1;
    }
  }
  return -1;
}

} // namespace aoc2015
