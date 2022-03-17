#include "2015/day1/aoc.h"
#include "2015/day2/aoc.h"
#include "2015/day3/aoc.h"
#include "2015/day4/aoc.h"
#include "2015/day5/aoc.h"
#include "2015/day6/aoc.h"
#include "2015/day7/aoc.h"
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
  auto p = aoc2015::day2(lv);
  REQUIRE(p.first == 1586300);
  REQUIRE(p.second == 3737498);
}

TEST_CASE("Perfectly Spherical Houses in a Vacuum", "[day3]") {
  line_view lv = load_file("../src/2015/day3/input");
  auto p = aoc2015::day3(lv);
  REQUIRE(p.first == 2565);
  REQUIRE(p.second == 2639);
}

TEST_CASE("The Ideal Stocking Stuffer", "[day4]") {
  char s1[] = "abcdef609043";
  char s2[] = "pqrstuv1048970";
  char s3[] = "bgvyzdsv254575";
  char s4[] = "bgvyzdsv1038736";

  REQUIRE(aoc2015::lead_zeros(aoc2015::md5sum(s1)) >= 5);
  REQUIRE(aoc2015::lead_zeros(aoc2015::md5sum(s2)) >= 5);
  REQUIRE(aoc2015::lead_zeros(aoc2015::md5sum(s3)) >= 5);
  REQUIRE(aoc2015::lead_zeros(aoc2015::md5sum(s4)) >= 6);
}

TEST_CASE("Doesn't He Have Intern-Elves For This?", "[day5]") {
  line_view lv{"adcccfadd", 9};
  REQUIRE(aoc2015::count_vowels(lv, "aeiou") == 2);
  REQUIRE(aoc2015::count_vowels(lv, "eiou") == 0);
  REQUIRE(aoc2015::is_nice(lv, 2));
  REQUIRE(aoc2015::is_nice(lv, 3));
  REQUIRE(!aoc2015::is_nice(lv, 4));

  const char* sub1[] = {"xy", "dx"};
  const char* sub2[] = {"xy", "fadd", "dx"};
  REQUIRE(lv.contains("fadd"));
  REQUIRE(lv.contains("ad"));
  REQUIRE(aoc2015::is_nice(lv, sub1, ARRAY_SIZE(sub1)));
  REQUIRE(!aoc2015::is_nice(lv, sub2, ARRAY_SIZE(sub2)));
  REQUIRE(aoc2015::is_interleaved(lv));
  REQUIRE(aoc2015::has_no_overlap_pair(lv));

  line_view ss = load_file("../src/2015/day5/input");
  auto p = aoc2015::day5(ss);
  REQUIRE(p.first == 255);
  REQUIRE(p.second == 55);
}

TEST_CASE("Probably a Fire Hazard", "[day6]") {
  aoc2015::grid<aoc2015::Bit, 1000> grid;
  grid.turn_on({0, 0}, {0, 999});
  REQUIRE(grid.store_.count() == 1000);

  aoc2015::grid<int8_t, 1000> grid2;
  grid2.toggle({0, 0}, {0, 999});
  REQUIRE(grid2.store_.count() == 2000);

  line_view lv = load_file("../src/2015/day6/input");
  auto p = aoc2015::day6(lv);
  REQUIRE(543903 == p.first);
  REQUIRE(14687245 == p.second);
}

TEST_CASE("Some Assembly Required", "[day 7]") {
  aoc2015::cals cals;
  cals.parse("1 OR 2 -> ab");
  printf("%d\n", cals.compute("ab").value);
}
