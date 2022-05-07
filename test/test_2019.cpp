#include "2019/day1/aoc.h"
#include "2019/day2/aoc.h"
#include "2019/day3/aoc.h"
#include "2019/day4/aoc.h"
#include "2019/day5/aoc.h"
#include "2019/day6/aoc.h"
#include "2019/day7/aoc.h"
#include "2019/day8/aoc.h"
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
  auto p = aoc2019::day7(lv);
  REQUIRE(272368 == p.first);
  REQUIRE(19741286 == p.second);
  // auto p = aoc2019::day7("3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5");
  // auto p = aoc2019::day7("3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,-5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10");
  // REQUIRE(139629729 == p.second);
}
