#include "2020/day1/aoc.h"
#include "2020/day2/aoc.h"
#include "2020/day3/aoc.h"
#include "catch.hpp"
#include <stdio.h>

TEST_CASE("Report Repair", "[2020]") {
  line_view lv = load_file("../src/2020/day1/input");
  auto p = aoc2020::day1(lv, 2020);
  REQUIRE(1019904 == p.first);
  REQUIRE(176647680 == p.second);
}

TEST_CASE("Password Philosophy", "[2020]") {
  line_view lv = load_file("../src/2020/day2/input");
  auto p = aoc2020::day2(lv);
  REQUIRE(564 == p.first);
  REQUIRE(325 == p.second);
}
