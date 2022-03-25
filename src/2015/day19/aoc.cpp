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
  // int shortest = INT32_MAX;
  // m.deduct(m.original, 0, &shortest);
  // m.transfer("e", 0, &shortest);
  std::vector<molecule::pattern> ps;
  const char* x = nullptr;
  m.parse_pattern(m.original, 0, ps, &x);
  std::for_each(ps.begin(), ps.end(), [](molecule::pattern p) { std::cout << p.depth << " -> " << p.lv << std::endl; });
  return {m.distinct(changes), 0};
}

} // namespace aoc2015
