#include "2015/day1/aoc.h"
#include "2015/day2/aoc.h"
#include "catch.hpp"
#include <stdio.h>

TEST_CASE("Not Quite Lisp", "[day1]") {
  line_view lv = load_file("../src/2015/day1/input");
  REQUIRE(aoc2015::day1(lv) == 74);
  REQUIRE(aoc2015::day1(lv, -1) == 1795);
}

TEST_CASE("parse box", "[day2]") {
  line_view lv1{"27x2x5\n", 7};
  auto b1 = aoc2015::parse_day2(lv1);
  auto a1 = b1.l == 27 && b1.w == 2 && b1.h == 5;
  REQUIRE(a1);
  line_view lv2{"29x13x26\n", 9};
  auto b2 = aoc2015::parse_day2(lv2);
  auto a2 = b2.l == 29 && b2.w == 13 && b2.h == 26;
  REQUIRE(a2);
}

TEST_CASE("I Was Told There Would Be No Math", "[day2]") {
  line_view lv = load_file("../src/2015/day2/input");
  printf("%d\n", aoc2015::day2(lv));
}
