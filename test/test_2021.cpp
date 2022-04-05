#include "2021/day1/aoc.h"
#include "2021/day2/aoc.h"
#include "2021/day3/aoc.h"
#include "catch.hpp"
#include <stdio.h>

TEST_CASE("Sonar Sweep", "[2021]") {
  line_view lv = load_file("../src/2021/day1/input");
  auto p = aoc2021::day1(lv);
  REQUIRE(1616 == p.first);
  REQUIRE(1645 == p.second);
}
