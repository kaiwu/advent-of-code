#include "aoc.h"

namespace aoc2015 {

int day19(line_view file) {
  molecule m;
  per_line(file, [&m](line_view lv) {
    m.parse(lv);
    return true;
  });
  std::map<int, std::vector<molecule::change>> changes;
  m.check(changes);
  return m.distinct(changes);
}

} // namespace aoc2015
