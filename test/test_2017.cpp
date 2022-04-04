#include "2017/day1/aoc.h"
#include "2017/day2/aoc.h"
#include "catch.hpp"
#include <stdio.h>

TEST_CASE("Inverse Captcha", "[2017]") {
  line_view lv = load_file("../src/2017/day1/input");
  REQUIRE(1253 == aoc2017::day1(lv));
  REQUIRE(4 == aoc2017::day1("1111"));
  REQUIRE(3 == aoc2017::day1("1122"));
  REQUIRE(1278 == aoc2017::day1part2(lv));
  REQUIRE(6 == aoc2017::day1part2("1212"));
  REQUIRE(0 == aoc2017::day1part2("1221"));
  REQUIRE(4 == aoc2017::day1part2("123425"));
  REQUIRE(12 == aoc2017::day1part2("123123"));
  REQUIRE(4 == aoc2017::day1part2("12131415"));
}

TEST_CASE("Corruption Checksum", "[2017]") {
  line_view lv = load_file("../src/2017/day2/input");
  REQUIRE(43074 == aoc2017::day2(lv));
}
