#include "aoc.h"
#include <vector>

namespace aoc2020 {

struct pos {
  int x;
  int y;
};

pos mov(pos p, int dx, int dy) { return {p.x + dx, p.y + dy}; }

void progress(pos p, pos* d1, pos* d2, int dx, const std::vector<line_view>& trees, int* count) {
  pos* d = dx > 0 ? d2 : d1;
  pos n = mov(p, d->x, d->y);
  if (size_t(n.y) < trees.size()) {
    const line_view& row = trees[n.y];
    if (size_t(n.x) < row.length) {
      const char* t = row.line + n.x;
      if (*t == '#') {
        *count += 1;
      }
      progress(n, d1, d2, 0, trees, count);
    } else {
      d2->x = n.x - row.length;
      d2->y = d1->y;
      // printf("delta %d %d\n", d2->x, d2->y);
      progress({0, p.y}, d1, d2, 1, trees, count);
    }
  }
}

int day3(line_view file) {
  std::vector<line_view> trees;
  per_line(file, [&trees](line_view lv) {
    trees.push_back({lv.line, lv.line + lv.length - 1});
    return true;
  });

  pos d1{3, 1};
  pos d2{0, 0};
  int count{0};
  progress({0, 0}, &d1, &d2, 0, trees, &count);

  return count;
}

} // namespace aoc2020
