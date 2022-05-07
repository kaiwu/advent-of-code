#include "2020/day1/aoc.h"
#include "2020/day2/aoc.h"
#include "2020/day3/aoc.h"
#include "2020/day4/aoc.h"
#include "2020/day5/aoc.h"
#include "2020/day6/aoc.h"
#include "2020/day7/aoc.h"
#include "2020/day8/aoc.h"
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

TEST_CASE("Toboggan Trajectory", "[2020]") {
  // line_view lv = load_file("../src/2020/day3/input0");
  line_view lv = load_file("../src/2020/day3/input");
  auto p = aoc2020::day3(lv);
  REQUIRE(242 == p.first);
  REQUIRE(2265549792 == p.second);
}

TEST_CASE("Passport Processing", "[2020]") {
  line_view lv = load_file("../src/2020/day4/input");
  auto p = aoc2020::day4(lv);
  REQUIRE(256 == p.first);
  REQUIRE(198 == p.second);
}

TEST_CASE("Binary Boarding", "[2020]") {
  // line_view lv("BFFFBBFRRR\nFFFBBBFRRR\nBBFFBBFRLL\n");
  line_view lv = load_file("../src/2020/day5/input");
  REQUIRE(842 == aoc2020::day5(lv));
}

TEST_CASE("Custom Customs", "[2020]") {
  line_view lv = load_file("../src/2020/day6/input");
  auto p = aoc2020::day6(lv);
  REQUIRE(7120 == p.first);
  REQUIRE(3570 == p.second);
}

TEST_CASE("Handy Haversacks", "[2020]") {
  line_view lv = load_file("../src/2020/day7/input");
  auto p = aoc2020::day7(lv, "shiny gold");
  REQUIRE(126 == p.first);
  REQUIRE(220149 == p.second);
}
