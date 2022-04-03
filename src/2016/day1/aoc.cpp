#include "aoc.h"

namespace aoc2016 {

instruction parse_day1(const char** pp) {
  instruction i;
  const char* p = *pp;
  i.direction = (*p++) == 'R' ? instruction::right : instruction::left;
  i.distance = 0;

  while (*p >= '0' && *p <= '9') {
    i.distance = i.distance * 10 + *p - '0';
    p++;
  }

  *pp = p;
  return i;
}

int day1(line_view file) {
  position x{position::north, 0, 0};
  std::vector<instruction> is;

  const char* p1 = file.line;
  const char* p2 = file.line + file.length;
  while (p1 < p2) {
    if (*p1 == 'R' || *p1 == 'L') {
      is.emplace_back(parse_day1(&p1));
    } else {
      p1++;
    }
  }
  position n = x.move(is);
  return x.blocks(n);
}

} // namespace aoc2016
