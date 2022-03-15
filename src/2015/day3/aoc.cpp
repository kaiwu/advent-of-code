#include "aoc.h"
#include <map>

namespace aoc2015 {

house move_day3(house h, dir d) {
  house n = h;
  switch (d) {
  case dir::up:
    n.y += 1;
    break;
  case dir::down:
    n.y -= 1;
    break;
  case dir::left:
    n.x -= 1;
    break;
  case dir::right:
    n.x += 1;
    break;
  }
  return n;
}

std::pair<size_t, size_t> day3(line_view lv) {
  house h{0, 0};
  house h1{0, 0};
  house h2{0, 0};
  std::map<house, size_t> m1{{h, 1}};
  std::map<house, size_t> m2{{h, 1}};
  house* hs[] = {&h1, &h2};

  for (size_t i = 0; i < lv.length; i++) {
    int x = i % 2;
    switch (lv.line[i]) {
    case '^':
      h = move_day3(h, dir::up);
      *hs[x] = move_day3(*hs[x], dir::up);
      break;
    case 'v':
      h = move_day3(h, dir::down);
      *hs[x] = move_day3(*hs[x], dir::down);
      break;
    case '>':
      h = move_day3(h, dir::right);
      *hs[x] = move_day3(*hs[x], dir::right);
      break;
    case '<':
      h = move_day3(h, dir::left);
      *hs[x] = move_day3(*hs[x], dir::left);
      break;
    default:
      break;
    }
    m1.insert({h, 1});
    m2.insert({*hs[x], 1});
  }
  return {m1.size(), m2.size()};
}

} // namespace aoc2015
