#include "aoc.h"
#include <unordered_map>

namespace aoc2017 {

void fix_subs(std::unordered_map<line_view, disc*>& ds) {
  for (auto& kv : ds) {
    if (kv.second->xp != nullptr) {
      const char* p1 = kv.second->xp;
      const char* p = p1;
      while (*p != '\n') {
        if (*p == ',') {
          kv.second->subs.push_back(ds[{p1, p}]);
          p1 = p + 2;
        }
        p++;
      }
      kv.second->subs.push_back(ds[{p1, p}]);
    }
  }
}

void depth(disc* d, int* dh) {
  if (d->subs.size() > 0) {
    *dh += 1;
    depth(d->subs[0], dh);
  }
}

void day7(line_view file, char name[]) {
  std::unordered_map<line_view, disc*> ds;
  per_line(file, [&ds](line_view lv) {
    const char* p = lv.contains("(");
    line_view name{lv.line, p - 1};
    ds.insert({name, new disc{lv, p}});
    return true;
  });
  fix_subs(ds);

  line_view x;
  int max{INT32_MIN};
  for (auto& kv : ds) {
    int d{1};
    depth(kv.second, &d);
    if (d > max) {
      max = d;
      x = kv.first;
    }
  }
  int i{0};
  per_char(x, [&name, &i](char c) {
    name[i++] = c;
    return true;
  });
}

} // namespace aoc2017
