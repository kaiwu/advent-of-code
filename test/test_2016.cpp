#include "2016/day1/aoc.h"
#include "2016/day2/aoc.h"
#include "catch.hpp"
#include <stdio.h>

TEST_CASE("No Time for a Taxicab", "[2016]") {
  line_view lv = load_file("../src/2016/day1/input");
  auto p = aoc2016::day1(lv);
  REQUIRE(298 == p.first);
  REQUIRE(158 == p.second);
}

TEST_CASE("Bathroom Security", "[2016]") {
  line_view lv = load_file("../src/2016/day2/input");
  REQUIRE(82958 == aoc2016::day2(lv));
}
