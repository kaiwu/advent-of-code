#include "aoc.h"
#include <vector>

namespace aoc2016 {

bool is_abba(const char* p) { return *p == *(p + 3) && *(p + 1) == *(p + 2) && *p != *(p + 1); }
bool is_aba(const char* p) { return *p == *(p + 2) && *p != *(p + 1); }
bool is_reverse(const char* p1, const char* p2) { return *p1 == *(p2 + 1) && *(p1 + 1) == *p2; }

std::vector<line_view> aba(const std::vector<line_view>& ls) {
  std::vector<line_view> vs;
  for (auto& l : ls) {
    const char* p = l.line;
    while (p < l.line + l.length - 2) {
      if (is_aba(p)) {
        vs.emplace_back(p, 3);
      }
      p++;
    }
  }
  return vs;
}

bool match_aba(const std::vector<line_view>& ls1, const std::vector<line_view>& ls2) {
  for (auto& l1 : ls1) {
    for (auto& l2 : ls2) {
      if (is_reverse(l1.line, l2.line)) {
        return true;
      }
    }
  }
  return false;
}

bool has_abba(const std::vector<line_view>& ls) {
  for (auto& l : ls) {
    const char* p = l.line;
    while (p < l.line + l.length - 3) {
      if (is_abba(p)) {
        return true;
      }
      p++;
    }
  }
  return false;
}

std::pair<int, int> day7(line_view file) {
  int t0{0}, t1{0};
  per_line(file, [&t0, &t1](line_view lv) {
    std::vector<line_view> g1;
    std::vector<line_view> g2;
    const char* p1 = lv.line;
    const char* p = p1;
    while (p < lv.line + lv.length) {
      if (*p == '[') {
        g1.emplace_back(p1, p);
        p1 = p + 1;
      }
      if (*p == ']') {
        g2.emplace_back(p1, p);
        p1 = p + 1;
      }
      p++;
    }
    g1.emplace_back(p1, p);

    t0 += int(has_abba(g1) && !has_abba(g2));
    t1 += int(match_aba(aba(g1), aba(g2)));
    return true;
  });
  return {t0, t1};
}

} // namespace aoc2016
