#include "2019/day1/aoc.h"
#include "2019/day2/aoc.h"
#include "2019/day3/aoc.h"
#include "2019/day4/aoc.h"
#include "2019/day5/aoc.h"
#include "2019/day6/aoc.h"
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

TEST_CASE("Crossed Wires", "[2019]") {
  line_view lv = load_file("../src/2019/day3/input");
  auto p = aoc2019::day3(lv);
  REQUIRE(19242 == p.first);
  REQUIRE(266 == p.second);
}

TEST_CASE("Secure Container", "[2019]") {
  auto p = aoc2019::day4("264793", "803935");
  REQUIRE(966 == p.first);
  REQUIRE(628 == p.second);
}

TEST_CASE("Sunny with a Chance of Asteroids", "[2019]") {
  line_view lv = load_file("../src/2019/day5/input");
  auto p = aoc2019::day5(lv);
  REQUIRE(6761139 == p.first);
  REQUIRE(9217546 == p.second);
}

TEST_CASE("Universal Orbit Map", "[2019]") {
  line_view lv = load_file("../src/2019/day6/input");
  auto p = aoc2019::day6(lv);
  REQUIRE(0 == p);
}
