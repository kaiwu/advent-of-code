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

int match_closest(wire ws[]) {
  day3point p1;
  day3point p2;
  ws[0].sort();
  ws[1].sort();
  match(ws[0].psh, ws[1].psv, &p1);
  match(ws[1].psh, ws[0].psv, &p2);
  day3point p = std::min(p1, p2);
  return p.distance();
}

int distance(const wire::line& l, day3point p) { return l.a.x == p.x ? std::abs(p.y - l.a.y) : std::abs(p.x - l.a.x); }
int distance(const wire::line& l, wire::line* ls) {
  int total{0};
  int i{0};
  while (ls[i].id != l.id) {
    total += ls[i++].length;
  }
  return total;
}

void match(int i, wire::line* ls1, wire::line* ls2, int* shorest, int max) {
  if (i < max) {
    for (int j = 1; j < max; j += 2) {
      day3point p;
      if (cross(ls1[i], ls2[j], &p)) {
        int s1 = distance(ls1[i], p) + distance(ls1[i], ls1);
        int s2 = distance(ls2[j], p) + distance(ls2[j], ls2);
        if (s1 + s2 < *shorest) {
          *shorest = s1 + s2;
        }
      }
    }
    match(i + 2, ls1, ls2, shorest, max);
  }
}

bool match(wire::line* ls1, wire::line* ls2, size_t n) {
  day3point p1;
  day3point p2;
  if (cross(ls1[n - 1], ls2[n], &p1)) {
    return true;
  }
  if (cross(ls2[n - 1], ls1[n], &p2)) {
    return true;
  }
  return false;
}

int match_earliest(wire ws[]) {
  size_t n = 1;
  while (n < ws[0].ps.size() && n < ws[1].ps.size()) {
    if (match(ws[0].ps.data(), ws[1].ps.data(), n)) {
      break;
    }
    n += 1;
  }
  int shorest{INT32_MAX};
  match(0, ws[0].ps.data(), ws[1].ps.data(), &shorest, n + 1);
  match(0, ws[1].ps.data(), ws[0].ps.data(), &shorest, n + 1);
  // printf("%d\n", shorest);
  return shorest;
}

std::pair<int, int> day3(line_view file) {
  wire ws[2];
  int i{0};
  per_line(file, [&ws, &i](line_view lv) {
    day3point cp{0, 0};
    ws[i++].parse(lv, &cp);
    return true;
  });
  // printf("%zu %zu\n", ws[0].ps.size(), ws[1].ps.size());
  return {match_earliest(ws), match_closest(ws)};
}

} // namespace aoc2019
