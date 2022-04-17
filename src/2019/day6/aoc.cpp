#include "aoc.h"
#include <algorithm>
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

void count(star* s, std::vector<star*>& vs, int* total, std::vector<star*>& v1, std::vector<star*>& v2) {
  // std::cout << s->name << std::endl;
  if (s->orbits.size() > 0) {
    std::vector<star*> orbits{s->orbits.begin(), s->orbits.end()};
    for (auto& x : orbits) {
      vs.push_back(x);
      count(x, vs, total, v1, v2);
      vs.pop_back();
    }
  }
  if (s->name == "YOU") {
    v1 = vs;
  }
  if (s->name == "SAN") {
    v2 = vs;
  }
  *total += vs.size();
}

void check(std::vector<star*> vs) {
  std::for_each(vs.begin(), vs.end(), [](star* s) { std::cout << s->name << " <- "; });
  std::cout << std::endl;
}

template <typename T>
static size_t common(const std::vector<T>& v1, const std::vector<T>& v2) {
  size_t i{0};
  while (i < v1.size() && i < v2.size()) {
    if (v1[i] != v2[i]) {
      return i;
    }
    i++;
  }
  return i;
}

std::pair<int, int> day6(line_view file) {
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
  std::vector<star*> v1;
  std::vector<star*> v2;
  count(stars["COM"], vs, &total, v1, v2);
  // check(v1);
  // check(v2);

  // printf("%zu %zu %zu\n", common(v1, v2), v1.size(), v2.size());
  size_t c = common(v1, v2);
  return {total, (v1.size() - c - 1) + (v2.size() - c - 1)};
}

} // namespace aoc2019
