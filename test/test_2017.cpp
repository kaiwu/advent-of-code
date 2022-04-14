#include "2017/day1/aoc.h"
#include "2017/day2/aoc.h"
#include "2017/day3/aoc.h"
#include "2017/day4/aoc.h"
#include "2017/day5/aoc.h"
#include "2017/day6/aoc.h"
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
  auto p = aoc2017::day2(lv);
  REQUIRE(43074 == p.first);
  REQUIRE(280 == p.second);
}

TEST_CASE("Spiral Memory", "[2017]") {
  REQUIRE(2 == aoc2017::day3(9));
  REQUIRE(2 == aoc2017::day3(11));
  REQUIRE(3 == aoc2017::day3(10));
  REQUIRE(4 == aoc2017::day3(13));
  REQUIRE(4 == aoc2017::day3(25));
  REQUIRE(430 == aoc2017::day3(312051));
  REQUIRE(312453 == aoc2017::day3part2(312051));
}

TEST_CASE("High-Entropy Passphrases", "[2017]") {
  line_view lv = load_file("../src/2017/day4/input");
  auto p = aoc2017::day4(lv);
  REQUIRE(386 == p.first);
  REQUIRE(208 == p.second);
}

TEST_CASE("A Maze of Twisty Trampolines, All Alike", "[2017]") {
  line_view lv = load_file("../src/2017/day5/input");
  // line_view lv = load_file("../src/2017/day5/input0");
  REQUIRE(360603 == aoc2017::day5(lv));
}

TEST_CASE("Memory Reallocation", "[2017]") {
  line_view lv = load_file("../src/2017/day6/input");
  // auto p = aoc2017::day6("0 2 7 0\n");
  // REQUIRE(5 == p.first);
  // REQUIRE(4 == p.second);
  auto p = aoc2017::day6(lv);
  REQUIRE(6681 == p.first);
  REQUIRE(2392 == p.second);
}
