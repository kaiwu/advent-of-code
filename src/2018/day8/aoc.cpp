#include "aoc.h"
#include <stack>
#include <vector>

namespace aoc2018 {

static void get_number(const char** pp, int* d) {
  const char* p = *pp;
  *d = 0;
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *pp = p;
}

struct header {
  int nodes;
  int metas;
};

int day8(line_view file) {
  std::vector<int> is;
  const char* p1 = file.line;
  const char* p2 = file.line + file.length;
  while (p1 < p2) {
    if (*p1 >= '0' && *p1 <= '9') {
      int d{0};
      get_number(&p1, &d);
      is.push_back(d);
    }
    p1++;
  }

  std::stack<header> hs;
  size_t index{0};
  int total{0};
  hs.push({is[index], is[index + 1]});
  index += 2;
  while (!hs.empty()) {
    auto& h = hs.top();
    if (h.nodes > 0) {
      hs.push({is[index], is[index + 1]});
      index += 2;
      h.nodes -= 1;
    } else {
      while (h.metas > 0) {
        total += is[index];
        index += 1;
        h.metas -= 1;
      }
      hs.pop();
    }
  }
  return total;
}

} // namespace aoc2018
