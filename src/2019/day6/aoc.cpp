#include "aoc.h"
#include <unordered_map>
#include <vector>

namespace aoc2019 {

star* find(std::unordered_map<line_view, star*>& stars, line_view lv) {
  auto it = stars.find(lv);
  star* s = nullptr;
  if (it == stars.end()) {
    s = new star{lv};
    stars.insert({lv, s});
  } else {
    s = it->second;
  }
  // std::cout << s->name << std::endl;
  return s;
}

void count(star* s, std::vector<star*>& vs, int* total) {
  std::cout << s->name << std::endl;
  if (s->orbits.size() > 0) {
    std::vector<star*> orbits{s->orbits.begin(), s->orbits.end()};
    for (auto& x : orbits) {
      vs.push_back(x);
      count(x, vs, total);
      vs.pop_back();
    }
  }
  *total += vs.size();
}

int day6(line_view file) {
  std::unordered_map<line_view, star*> stars;
  per_line(file, [&stars](line_view lv) {
    const char* p = lv.contains(")");
    star* s1 = find(stars, line_view{lv.line, p});
    star* s2 = find(stars, line_view{p + 1, lv.line + lv.length - 1});
    s1->orbits.insert(s2);
    return true;
  });

  int total{0};
  std::vector<star*> vs;
  count(stars["COM"], vs, &total);
  return total;
}

} // namespace aoc2019
