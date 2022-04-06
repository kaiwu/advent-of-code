#include "2018/day1/aoc.h"
#include "2018/day2/aoc.h"
#include "2018/day3/aoc.h"
#include "catch.hpp"
#include <stdio.h>
#include <string.h>

TEST_CASE("Chronal Calibration", "[2018]") {
  line_view lv = load_file("../src/2018/day1/input");
  REQUIRE(522 == aoc2018::day1(lv));
  REQUIRE(73364 == aoc2018::day1part2(lv));
  // REQUIRE(10 == aoc2018::day1part2("+3\n+3\n+4\n-2\n-4"));
  // REQUIRE(5 == aoc2018::day1part2("-6\n+3\n+8\n+5\n-6"));
  // REQUIRE(14 == aoc2018::day1part2("+7\n+7\n-2\n-7\n-4"));
}

TEST_CASE("Inventory Management System", "[2018]") {
  line_view lv = load_file("../src/2018/day2/input");
  char common[26] = {0};
  auto p = aoc2018::day2(lv, common);
  REQUIRE(6642 == p);
  REQUIRE(strcmp("cvqlbidheyujgtrswxmckqnap", common) == 0);
}

TEST_CASE("No Matter How You Slice It", "[2018]") {
  line_view lv = load_file("../src/2018/day3/input");
  auto p = aoc2018::day3(lv, 1);
  REQUIRE(109785 == p.first);
  REQUIRE(504 == p.second);
}
