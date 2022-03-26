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
  int steps = 0;

  line_view lv = m.original;

  do {
    lv = m.replace(lv, &steps);
    printf("%d\n", steps);

    std::vector<molecule::pattern> ps;
    const char* x = nullptr;
    m.parse_pattern(lv, 0, ps, &x);
    std::for_each(ps.begin(), ps.end(),
                  [](molecule::pattern p) { std::cout << p.depth << " -> " << p.lv << std::endl; });
    if (ps[0].lv.contains("Y")) {
      std::vector<line_view> ys;
      m.parse_y(ps[0].lv, ys);
      for (auto y : ys) {
        if (m.transfers.find(y) == m.transfers.end()) {
          line_view to = m.deduce(y, &steps);
          lv = m.replace(lv, {y, to}, y.line);
          break;
        }
      }
    } else {
      line_view to = m.deduce(ps[0].lv, &steps);
      lv = m.replace(lv, {ps[0].lv, to}, ps[0].lv.line);
    }
  } while (true);

  return {m.distinct(changes), 0};
}

} // namespace aoc2015
