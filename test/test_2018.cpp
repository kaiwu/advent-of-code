#include "2018/day1/aoc.h"
#include "2018/day2/aoc.h"
#include "2018/day3/aoc.h"
#include "2018/day4/aoc.h"
#include "2018/day5/aoc.h"
#include "2018/day6/aoc.h"
#include "2018/day7/aoc.h"
#include "catch.hpp"
#include <stdio.h>
#include <string.h>

TEST_CASE("Chronal Calibration", "[2018]") {
  line_view lv = load_file("../src/2018/day1/input");
  REQUIRE(522 == aoc2018::day1(lv));
  REQUIRE(73364 == aoc2018::day1part2(lv));
  // REQUIRE(10 == aoc2018::day1part2("+3\n+3\n+4\n-2\n-4"));
  // REQUIRE(5 == aoc2018::day1part2("-6\n+3\n+8\n+5\n-6"));
  // REQUIRE(14 == aoc2018::day1part2("+7\n+7\n-2\n-7\n-4"));
}

TEST_CASE("Inventory Management System", "[2018]") {
  line_view lv = load_file("../src/2018/day2/input");
  char common[26] = {0};
  auto p = aoc2018::day2(lv, common);
  REQUIRE(6642 == p);
  REQUIRE(strcmp("cvqlbidheyujgtrswxmckqnap", common) == 0);
}

TEST_CASE("No Matter How You Slice It", "[2018]") {
  line_view lv = load_file("../src/2018/day3/input");
  auto p = aoc2018::day3(lv, 1);
  REQUIRE(109785 == p.first);
  REQUIRE(504 == p.second);
}

TEST_CASE("Repose Record", "[2018]") {
  line_view lv = load_file("../src/2018/day4/input");
  auto p = aoc2018::day4(lv);
  REQUIRE(14346 == p.first);
  REQUIRE(5705 == p.second);
}

TEST_CASE("Alchemical Reduction", "[2018]") {
  line_view lv = load_file("../src/2018/day5/input");
  auto p = aoc2018::day5(lv);
  REQUIRE(11042 == p.first);
  REQUIRE(6872 == p.second);
}

TEST_CASE("Chronal Coordinates", "[2018]") {
  line_view lv = load_file("../src/2018/day6/input");
  auto p = aoc2018::day6(lv, 10000);
  REQUIRE(3260 == p.first);
  REQUIRE(42535 == p.second);
}

TEST_CASE("The Sum of Its Parts", "[2018]") {
  // line_view lv = load_file("../src/2018/day7/input0");
  line_view lv = load_file("../src/2018/day7/input");
  char sequence[100] = {0};
  REQUIRE(941 == aoc2018::day7(lv, sequence));
  REQUIRE(strcmp("BGKDMJCNEQRSTUZWHYLPAFIVXO", sequence) == 0);
}
