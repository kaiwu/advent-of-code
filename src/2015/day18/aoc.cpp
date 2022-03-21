#include "aoc.h"
namespace aoc2015 {

int day18(line_view file, int d) {
  yard y;
  y.parse(file);
  y.turns(d);
  return y.count();
}

} // namespace aoc2015
