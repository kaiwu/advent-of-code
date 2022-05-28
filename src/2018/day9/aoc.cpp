#include "aoc.h"

namespace aoc2018 {

int day9(int players, int point) {
  marble_circle mc(point, players);
  mc.alloc(23);
  return mc.high();
}

} // namespace aoc2018
