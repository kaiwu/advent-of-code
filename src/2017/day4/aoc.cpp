#include "aoc.h"
#include <vector>

namespace aoc2017 {

typedef bool (*match_f)(const char*, const char*);
bool match(const char* p1, const char* p2) {
  auto is_az = [](char c) { return c >= 'a' && c <= 'z'; };
  while (is_az(*p1) && is_az(*p2)) {
    if (*p1++ != *p2++) {
      return false;
    }
  }
  return !is_az(*p1) && !is_az(*p2);
}

bool anagram(const char* p1, const char* p2) {
  auto is_az = [](char c) { return c >= 'a' && c <= 'z'; };
  auto len = [&is_az](const char* p, int is[]) {
    const char* p0 = p;
    while (is_az(*p)) {
      is[int(*p - 'a')]++;
      p++;
    }
    return p - p0;
  };
  int is1[26] = {0};
  int is2[26] = {0};
  int l1 = len(p1, is1);
  int l2 = len(p2, is2);
  if (l1 != l2) {
    return false;
  }
  for (int i = 0; i < 26; i++) {
    if (is1[i] != is2[i]) {
      return false;
    }
  }
  return true;
}

bool compare(size_t i, const std::vector<const char*>& ps, match_f f) {
  if (i < ps.size() - 1) {
    for (size_t j = i + 1; j < ps.size(); j++) {
      if (f(ps[i], ps[j])) {
        return false;
      }
    }
    return compare(i + 1, ps, f);
  }
  return true;
}

bool is_valid(line_view lv, match_f f) {
  const char* p = lv.line;
  std::vector<const char*> ps;
  ps.push_back(p);
  while (p < lv.line + lv.length) {
    if (*p == ' ') {
      ps.push_back(p + 1);
    }
    p++;
  }
  return compare(0, ps, f);
}

std::pair<int, int> day4(line_view file) {
  int t0{0};
  int t1{0};
  per_line(file, [&t0, &t1](line_view lv) {
    if (is_valid(lv, match)) {
      t0 += 1;
    }
    if (is_valid(lv, anagram)) {
      t1 += 1;
    }
    return true;
  });
  return {t0, t1};
}

} // namespace aoc2017
