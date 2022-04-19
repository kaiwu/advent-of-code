#include "2019/day1/aoc.h"
#include "2019/day2/aoc.h"
#include "2019/day3/aoc.h"
#include "2019/day4/aoc.h"
#include "2019/day5/aoc.h"
#include "2019/day6/aoc.h"
#include "2019/day7/aoc.h"
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
  REQUIRE(312697 == p.first);
  REQUIRE(466 == p.second);
}

TEST_CASE("Amplification Circuit", "[2019]") {
  line_view lv = load_file("../src/2019/day7/input");
  REQUIRE(272368 == aoc2019::day7(lv));
  // clang-format off
  // REQUIRE(43210 == aoc2019::day7(line_view{"3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0"}));
  // REQUIRE(54321 == aoc2019::day7(line_view{"3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0"}));
  // REQUIRE(65210 == aoc2019::day7(line_view{"3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0"}));
  // clang-format on
}
