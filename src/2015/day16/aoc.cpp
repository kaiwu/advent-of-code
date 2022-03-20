#include "aoc.h"
namespace aoc2015 {

bool like(const sue& s1, const sue& s2) { return s1.like(s2); }
bool like_range(const sue& s1, const sue& s2) { return s1.like_range(s2); }

std::pair<int, int> day16(line_view file) {
  aunts as;
  per_line(file, [&as](line_view lv) {
    as.parse(lv);
    return true;
  });

  sue x{3, 7, 2, 3, 0, 0, 5, 3, 2, 1};
  return {as.filter(x, like), as.filter(x, like_range)};
}
} // namespace aoc2015
