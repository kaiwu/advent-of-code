#pragma once
#include "common.h"
#include <iostream>

namespace aoc2020 {

struct passport {
  line_view byr;
  line_view iyr;
  line_view eyr;
  line_view hgt;
  line_view hcl;
  line_view ecl;
  line_view pid;
  line_view cid;

  friend std::ostream& operator<<(std::ostream& o, const passport& p) {
    o << p.byr << " " << p.iyr << " " << p.eyr << " ";
    o << p.hgt << " " << p.hcl << " " << p.ecl << " ";
    o << p.pid << " " << p.cid << " ";
    return o;
  }

  void get_number(const char** pp, int* d) {
    const char* p = *pp;
    while (*p >= '0' && *p <= '9') {
      *d = *d * 10 + *p - '0';
      p++;
    }
    *pp = p;
  }

  typedef bool (passport::*cf)(line_view);

  template <int A, int B, int C>
  bool chk1(line_view lv) {
    int y{0};
    const char* p = lv.line;
    get_number(&p, &y);
    return lv.length == A && y >= B && y <= C;
  }

  bool chk2(line_view lv) {
    int d{0};
    const char* p = lv.line;
    get_number(&p, &d);
    bool b1 = (*p == 'c' && *(p + 1) == 'm') && d >= 150 && d <= 193;
    bool b2 = (*p == 'i' && *(p + 1) == 'n') && d >= 59 && d <= 76;
    return b1 || b2;
  }

  bool chk3(line_view lv) {
    static const char* cs[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    for (auto c : cs) {
      if (lv == c) {
        return true;
      }
    }
    return false;
  }

  template <int A, char B, char C>
  bool chk4(line_view lv) {
    const char* p = lv.line;
    for (int i = 0; i < A; i++) {
      if (*(p + i) < B || *(p + i) > C) {
        return false;
      }
    }
    return lv.length == A;
  }

  bool chk5(line_view lv) {
    const char* p = lv.line + 1;
    auto is_az = [](char c) { return c >= 'a' && c <= 'z'; };
    auto is_09 = [](char c) { return c >= '0' && c <= '9'; };
    while (p < lv.line + lv.length) {
      if (!is_az(*p) && !is_09(*p)) {
        return false;
      }
      p++;
    }
    return *lv.line == '#' && lv.length == 7;
  }

  // byr (Birth Year) - four digits; at least 1920 and at most 2002.
  // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
  // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
  // hgt (Height) - a number followed by either cm or in:
  // If cm, the number must be at least 150 and at most 193.
  // If in, the number must be at least 59 and at most 76.
  // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
  // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
  // pid (Passport ID) - a nine-digit number, including leading zeroes.
  // cid (Country ID) - ignored, missing or not.

  void is_valid(bool* b1, bool* b2) {
    *b1 = byr.length > 0 && iyr.length > 0 && eyr.length > 0 && hgt.length > 0 && hcl.length > 0 && ecl.length > 0 &&
          pid.length > 0;

    *b2 = false;
    if (*b1) {
      struct {
        cf f;
        line_view* field;
      } checkers[] = {
          {&passport::chk1<4, 1920, 2002>, &byr},
          {&passport::chk1<4, 2010, 2020>, &iyr},
          {&passport::chk1<4, 2020, 2030>, &eyr},
          {&passport::chk2, &hgt},
          {&passport::chk5, &hcl},
          {&passport::chk3, &ecl},
          {&passport::chk4<9, '0', '9'>, &pid},
      };
      for (auto c : checkers) {
        if (!((this->*(c.f))(*c.field))) {
          return;
        }
      }
      *b2 = true;
    }
  }

  passport(const char* p1, const char* p2) {
    struct {
      line_view* field;
      const char* label;
    } attributes[] = {{&byr, "byr"}, {&iyr, "iyr"}, {&eyr, "eyr"}, {&hgt, "hgt"},
                      {&hcl, "hcl"}, {&ecl, "ecl"}, {&pid, "pid"}, {&cid, "cid"}};

    auto set_field = [&attributes](const char* p1, const char* p2) {
      auto match = [](const char* x, const char* y) -> bool {
        for (int i : {0, 1, 2}) {
          if (*(x + i) != *(y - (3 - i))) {
            return false;
          }
        }
        return true;
      };
      for (auto& a : attributes) {
        if (match(a.label, p1)) {
          *a.field = line_view{p1 + 1, p2};
          break;
        }
      }
    };

    const char* p = p1;
    while (p < p2) {
      if (*p == ':') {
        p1 = p;
      }
      if (*p == ' ' || *p == '\n') {
        set_field(p1, p);
      }
      p++;
    }
    set_field(p1, p);
  }
};

std::pair<int, int> day4(line_view);
} // namespace aoc2020
