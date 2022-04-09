#include "2016/day1/aoc.h"
#include "2016/day2/aoc.h"
#include "2016/day3/aoc.h"
#include "2016/day4/aoc.h"
#include "2016/day5/aoc.h"
#include "catch.hpp"
#include <stdio.h>
#include <string.h>

TEST_CASE("No Time for a Taxicab", "[2016]") {
  line_view lv = load_file("../src/2016/day1/input");
  auto p = aoc2016::day1(lv);
  REQUIRE(298 == p.first);
  REQUIRE(158 == p.second);
}

TEST_CASE("Bathroom Security", "[2016]") {
  line_view lv = load_file("../src/2016/day2/input");
  char codes[6] = {0};
  int code = aoc2016::day2(lv, codes);
  REQUIRE(82958 == code);
  REQUIRE(strcmp(codes, "B3DB8") == 0);
}

TEST_CASE("Squares With Three Sides", "[2016]") {
  line_view lv = load_file("../src/2016/day3/input");
  auto p = aoc2016::day3(lv);
  REQUIRE(862 == p.first);
  REQUIRE(1577 == p.second);
}

TEST_CASE("Security Through Obscurity", "[2016]") {
  line_view lv = load_file("../src/2016/day4/input");
  auto p = aoc2016::day4(lv);
  REQUIRE(185371 == p.first);
  REQUIRE(984 == p.second);
}
