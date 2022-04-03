#include "2016/day1/aoc.h"
#include "catch.hpp"
#include <stdio.h>

TEST_CASE("No Time for a Taxicab", "[day1]") {
  line_view lv = load_file("../src/2016/day1/input");
  REQUIRE(298 == aoc2016::day1(lv));
  // printf("%d\n", aoc2016::day1("R2, R2, R2"));
  // printf("%d\n", aoc2016::day1("R5, L5, R5, R3"));
}
