#include "aoc.h"
#include <map>
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
  size_t id;
};

// static void check(const std::map<int, std::vector<int>>& m) {
//   for (auto& kv : m) {
//     printf("%d -> ", kv.first);
//     for (auto x : kv.second) {
//       printf("%d ", x);
//     }
//     printf("\n");
//   }
// }

static int eval(int index, const std::map<int, std::vector<int>>& ms, const std::map<int, std::vector<int>>& mr) {
  auto it = ms.find(index);
  auto jt = mr.find(index);
  if (it != ms.end() && jt == mr.end()) {
    return it->second[0];
  }
  if (it != ms.end() && jt != mr.end()) {
    auto rs = it->second;
    auto xs = jt->second;
    int d{0};
    for (auto& r : rs) {
      if (size_t(r) <= xs.size()) {
        d += eval(xs[r - 1], ms, mr);
      }
    }
    return d;
  }
  return 0;
}

std::pair<int, int> day8(line_view file) {
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
  std::map<int, std::vector<int>> mr;
  std::map<int, std::vector<int>> ms;
  size_t index{0};
  int total{0};
  hs.push({is[index], is[index + 1], index});
  index += 2;
  while (!hs.empty()) {
    auto& h = hs.top();
    if (h.nodes > 0) {
      hs.push({is[index], is[index + 1], index});
      mr[h.id].push_back(index);
      index += 2;
      h.nodes -= 1;
    } else {
      int sub{0};
      while (h.metas > 0) {
        total += is[index];
        ms[h.id].push_back(is[index]);
        sub += is[index];
        index += 1;
        h.metas -= 1;
      }
      if (mr.find(h.id) == mr.end()) {
        ms[h.id] = {sub};
      }
      hs.pop();
    }
  }

  int d = eval(0, ms, mr);
  return {total, d};
}

} // namespace aoc2018
