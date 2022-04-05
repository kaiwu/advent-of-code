#include "2019/day1/aoc.h"
#include "2019/day2/aoc.h"
#include "catch.hpp"
#include <stdio.h>

TEST_CASE("The Tyranny of the Rocket Equation", "[2019]") {
  line_view lv = load_file("../src/2019/day1/input");
  REQUIRE(3471229 == aoc2019::day1(lv));
  REQUIRE(5203967 == aoc2019::day1part2(lv));
  REQUIRE(50346 == aoc2019::day1part2("100756"));
}

TEST_CASE("1202 Program Alarm", "[2019]") {
  line_view lv = load_file("../src/2019/day2/input");
  auto p = aoc2019::day2(lv);
  REQUIRE(11590668 == p.first);
  REQUIRE(2254 == p.second);
}
