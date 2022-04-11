#include "aoc.h"
#include <algorithm>
#include <vector>

namespace aoc2020 {

// row 0 - 127
// col 0 - 7
static void missing(const std::vector<seat>& seats, std::vector<seat>& miss) {
  static int plane[128 * 8] = {0};
  for (auto& s : seats) {
    plane[8 * s.row + s.col] = 1;
  }
  for (size_t i = 0; i < ARRAY_SIZE(plane); i++) {
    if (plane[i] == 0) {
      int r = i / 8;
      int c = i % 8;
      if (r != 0 && r != 127) {
        miss.emplace_back(seat{r, c});
      }
    }
  }
}

int day5(line_view file) {
  std::vector<seat> seats;
  per_line(file, [&seats](line_view lv) {
    seats.emplace_back(lv);
    return true;
  });
  std::vector<seat> miss;
  missing(seats, miss);
  // std::for_each(miss.begin(), miss.end(), [](const seat& s) { printf("%d %d %d\n", s.row, s.col, s.id()); });
  std::sort(seats.begin(), seats.end());
  return seats[seats.size() - 1].id();
}

} // namespace aoc2020
