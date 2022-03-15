#include "catch.hpp"
#include "2015/day1/aoc.h"
#include <stdio.h>

TEST_CASE("Not Quite Lisp", "[]") {
  line_view lv = load_file("../src/2015/day1/input");
  REQUIRE(aoc2015::day1(lv) == 74);
  REQUIRE(aoc2015::day1(lv, -1) == 1795);
}
