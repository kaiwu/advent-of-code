#include "aoc.h"

namespace aoc2018 {

size_t day9(size_t players, size_t point) {
  marble_circle mc(point, players);
  mc.alloc(1, 7, 23);
  return mc.high();
}

} // namespace aoc2018
