#include "aoc.h"

namespace aoc2015 {

std::pair<int, int> day19(line_view file) {
  molecule m;
  per_line(file, [&m](line_view lv) {
    m.parse(lv);
    return true;
  });
  std::map<int, std::vector<molecule::change>> changes;
  m.check(changes);
  int shortest = INT32_MAX;
  m.deduct(m.original, 0, &shortest);
  return {m.distinct(changes), shortest};
}

} // namespace aoc2015
