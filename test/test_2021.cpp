#include "2021/day1/aoc.h"
#include "2021/day2/aoc.h"
#include "2021/day3/aoc.h"
#include "2021/day4/aoc.h"
#include "2021/day5/aoc.h"
#include "2021/day6/aoc.h"
#include "2021/day7/aoc.h"
#include "2021/day8/aoc.h"
#include "catch.hpp"
#include <stdio.h>

TEST_CASE("Sonar Sweep", "[2021]") {
  line_view lv = load_file("../src/2021/day1/input");
  auto p = aoc2021::day1(lv);
  REQUIRE(1616 == p.first);
  REQUIRE(1645 == p.second);
}

TEST_CASE("Dive!", "[2021]") {
  line_view lv = load_file("../src/2021/day2/input");
  auto p = aoc2021::day2(lv);
  REQUIRE(1762050 == p.first);
  REQUIRE(1855892637 == p.second);
}

TEST_CASE("Binary Diagnostic", "[2021]") {
  line_view lv = load_file("../src/2021/day3/input");
  // line_view lv = load_file("../src/2021/day3/input0");
  auto p = aoc2021::day3(lv);
  REQUIRE(3885894 == p.first);
  REQUIRE(4375225 == p.second);
}

TEST_CASE("Giant Squid", "[2021]") {
  line_view lv = load_file("../src/2021/day4/input");
  auto p = aoc2021::day4(lv);
  REQUIRE(5685 == p.first);
  REQUIRE(21070 == p.second);
}

TEST_CASE("Hydrothermal Venture", "[2021]") {
  line_view lv = load_file("../src/2021/day5/input");
  auto p = aoc2021::day5(lv);
  REQUIRE(5774 == p.first);
  REQUIRE(18423 == p.second);
}

TEST_CASE("Lanternfish", "[2021]") {
  // line_view lv("3,4,3,1,2");
  line_view lv = load_file("../src/2021/day6/input");
  // REQUIRE(26 == aoc2021::day6(lv, 18));
  // REQUIRE(5934 == aoc2021::day6(lv, 80));
  // REQUIRE(26984457539 == aoc2021::day6(lv, 256));
  REQUIRE(379114 == aoc2021::day6(lv, 80));
  REQUIRE(1702631502303 == aoc2021::day6(lv, 256));
}

TEST_CASE("The Treachery of Whales", "[2021]") {
  line_view lv = load_file("../src/2021/day7/input");
  // auto p = aoc2021::day7("16,1,2,0,4,2,7,1,2,14");
  auto p = aoc2021::day7(lv);
  REQUIRE(354129 == p.first);
  REQUIRE(98905973 == p.second);
}
