#include "aoc.h"

namespace aoc2015 {

std::pair<int, int> day13(line_view file, const char* x) {
  party p;
  per_line(file, [&p](line_view lv) {
    p.parse(lv);
    return true;
  });
  if (x != nullptr) {
    p.add(x, 0);
  }
  return p.arrange();
}

} // namespace aoc2015
