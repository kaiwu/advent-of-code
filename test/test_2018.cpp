#include "2018/day1/aoc.h"
#include "catch.hpp"
#include <stdio.h>

TEST_CASE("Chronal Calibration", "[2018]") {
  line_view lv = load_file("../src/2018/day1/input");
  REQUIRE(522 == aoc2018::day1(lv));
  REQUIRE(73364 == aoc2018::day1part2(lv));
  // REQUIRE(10 == aoc2018::day1part2("+3\n+3\n+4\n-2\n-4"));
  // REQUIRE(5 == aoc2018::day1part2("-6\n+3\n+8\n+5\n-6"));
  // REQUIRE(14 == aoc2018::day1part2("+7\n+7\n-2\n-7\n-4"));
}
