#include "2015/day1/aoc.h"
#include "2015/day10/aoc.h"
#include "2015/day11/aoc.h"
#include "2015/day12/aoc.h"
#include "2015/day13/aoc.h"
#include "2015/day14/aoc.h"
#include "2015/day15/aoc.h"
#include "2015/day16/aoc.h"
#include "2015/day17/aoc.h"
#include "2015/day18/aoc.h"
#include "2015/day2/aoc.h"
#include "2015/day3/aoc.h"
#include "2015/day4/aoc.h"
#include "2015/day5/aoc.h"
#include "2015/day6/aoc.h"
#include "2015/day7/aoc.h"
#include "2015/day8/aoc.h"
#include "2015/day9/aoc.h"
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

TEST_CASE("Some Assembly Required", "[day7]") {
  aoc2015::cals cals;
  cals.parse("1 -> ab");
  cals.parse("8 RSHIFT ab -> x");
  cals.parse("1 LSHIFT x -> ac");
  cals.parse("ac OR ab -> ae");
  cals.parse("NOT x -> f");
  REQUIRE(1 == cals.compute("ab").value);
  REQUIRE(4 == cals.compute("x").value);
  REQUIRE(16 == cals.compute("ac").value);
  REQUIRE(17 == cals.compute("ae").value);
  REQUIRE(65531 == cals.compute("f").value);

  line_view lv = load_file("../src/2015/day7/input");
  auto r1 = aoc2015::day7(lv, "a");
  auto r2 = aoc2015::day7(lv, "a", "3176 -> b");

  REQUIRE(3176 == r1.value);
  REQUIRE(14710 == r2.value);
}

TEST_CASE("Matchsticks", "[day8]") {
  line_view lv = load_file("../src/2015/day8/input");
  auto p = aoc2015::day8(lv);
  REQUIRE(1371 == p.first);
  REQUIRE(2117 == p.second);
}

TEST_CASE("All in a Single Night", "[day9]") {
  line_view lv = load_file("../src/2015/day9/input");
  auto p = aoc2015::day9(lv);
  REQUIRE(117 == p.first);
  REQUIRE(909 == p.second);
}

TEST_CASE("Elves Look, Elves Say", "[day10]") {
  REQUIRE(329356 == aoc2015::day10("3113322113", 40));
  REQUIRE(4666278 == aoc2015::day10("3113322113", 50));
}

TEST_CASE("Corporate Policy", "[day11]") {
  REQUIRE(strcmp(aoc2015::day11("hxbxwxba"), "hxbxxyzz") == 0);
  REQUIRE(strcmp(aoc2015::day11("hxbxxyzz"), "hxcaabcc") == 0);
}

TEST_CASE("JSAbacusFramework.io", "[day12]") {
  // printf("%d\n", aoc2015::day12_part2("[{ 5 {red1} {3{4 {10}}3}} 10 red 10]"));
  line_view lv = load_file("../src/2015/day12/input");
  REQUIRE(156366 == aoc2015::day12(lv));
  REQUIRE(96852 == aoc2015::day12_part2(lv));
}

TEST_CASE("Knights of the Dinner Table", "[day13]") {
  line_view lv = load_file("../src/2015/day13/input");
  auto p1 = aoc2015::day13(lv);
  REQUIRE(-638 == p1.first);
  REQUIRE(709 == p1.second);

  auto p2 = aoc2015::day13(lv, "Wukai");
  REQUIRE(-679 == p2.first);
  REQUIRE(668 == p2.second);
}

TEST_CASE("Reindeer Olympics", "[day14]") {
  line_view lv = load_file("../src/2015/day14/input");
  auto p = aoc2015::day14(lv, 2503);
  REQUIRE(2640 == p.first);
  REQUIRE(1102 == p.second);
}

TEST_CASE("Science for Hungry People", "[day15]") {
  line_view lv = load_file("../src/2015/day15/input");
  REQUIRE(21367368 == aoc2015::day15(lv));
  int cals = 500;
  REQUIRE(1766400 == aoc2015::day15(lv, &cals));
}

TEST_CASE("Aunt Sue", "[day16]") {
  line_view lv = load_file("../src/2015/day16/input");
  auto p = aoc2015::day16(lv);
  REQUIRE(103 == p.first);
  REQUIRE(405 == p.second);
}

TEST_CASE("No Such Thing as Too Much", "[day17]") {
  line_view lv = load_file("../src/2015/day17/input");
  auto p = aoc2015::day17(lv, 150);
  REQUIRE(654 == p.first);
  REQUIRE(57 == p.second);

}

TEST_CASE("Like a GIF For Your Yard", "[day18]") {
}
