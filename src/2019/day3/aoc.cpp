#include "aoc.h"

namespace aoc2019 {

bool cross(const wire::line& lh, const wire::line& lv, day3point* p) {
  auto in_range = [](int x, int a, int b) {
    int min = std::min(a, b);
    int max = std::max(a, b);
    return x >= min && x <= max;
  };
  bool b1 = in_range(lv.a.x, lh.a.x, lh.b.x);
  bool b2 = in_range(lh.a.y, lv.a.y, lv.b.y);
  if (b1 && b2) {
    *p = {lv.a.x, lh.a.y};
    return true;
  }
  return false;
}

void match(const std::vector<wire::line>& lhs, const std::vector<wire::line>& lvs, day3point* p) {
  for (auto& lh : lhs) {
    for (auto& lv : lvs) {
      if (cross(lh, lv, p)) {
        return;
      }
    }
  }
}

int day3(line_view file) {
  wire ws[2];
  day3point mp{0, 0};
  int i{0};
  per_line(file, [&ws, &mp, &i](line_view lv) {
    day3point cp{0, 0};
    ws[i++].parse(lv, &cp, &mp);
    return true;
  });
  ws[0].sort();
  ws[1].sort();
  day3point p1;
  day3point p2;
  match(ws[0].psh, ws[1].psv, &p1);
  match(ws[1].psh, ws[0].psv, &p2);
  day3point p = std::min(p1, p2);
  return p.distance() ;
}

} // namespace aoc2019
