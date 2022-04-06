#include "aoc.h"

namespace aoc2018 {

std::pair<int, int> day3(line_view file, int x) {

  fabric* f = new fabric;
  std::vector<claim> cs;
  per_line(file, [&f, &cs](line_view lv) {
    f->parse(lv, cs);
    return true;
  });

  int id{0};
  for (auto& c : cs) {
    if (!f->overlap(c)) {
      id = c.id;
    }
  }

  return {f->count(x), id};
}

} // namespace aoc2018
