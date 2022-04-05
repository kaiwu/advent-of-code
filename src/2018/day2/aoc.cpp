#include "aoc.h"
#include <vector>

namespace aoc2018 {

int exactly(const ascii_count& ac, int x) {
  for (char i = 'a'; i <= 'z'; i++) {
    if (ac.count[int(i)] == x) {
      return 1;
    }
  }
  return 0;
}

bool almost(line_view lv1, line_view lv2, char comm[]) {
  const char* p1 = lv1.line;
  const char* p2 = lv2.line;
  int x{0};
  int i{0};
  while (p1 < lv1.line + lv1.length - 1 && x < 2) {
    if (*p1 == *p2) {
      comm[i++] = *p1;
    } else {
      x++;
    }
    p1++;
    p2++;
  }
  return x == 1;
}

void diff(size_t i, const std::vector<line_view>& ls, char comm[]) {
  if (i < ls.size() - 1) {
    for (size_t j = i + 1; j < ls.size(); j++) {
      if (almost(ls[i], ls[j], comm)) {
        return;
      }
    }
    diff(i + 1, ls, comm);
  }
}

int day2(line_view file, char comm[]) {
  int exactly2{0};
  int exactly3{0};
  std::vector<line_view> ls;

  per_line(file, [&exactly2, &exactly3, &ls](line_view lv) {
    ls.push_back(lv);
    ascii_count ac(lv);
    exactly2 += exactly(ac, 2);
    exactly3 += exactly(ac, 3);
    return true;
  });

  diff(0, ls, comm);

  return exactly2 * exactly3;
}

} // namespace aoc2018
