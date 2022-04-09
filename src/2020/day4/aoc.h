#pragma once
#include "common.h"
#include <iostream>

namespace aoc2020 {

struct passwort {
  line_view byr;
  line_view iyr;
  line_view eyr;
  line_view hgt;
  line_view hcl;
  line_view ecl;
  line_view pid;
  line_view cid;

  friend std::ostream& operator<<(std::ostream& o, const passwort& p) {
    o << p.byr << " " << p.iyr << " " << p.eyr << " ";
    o << p.hgt << " " << p.hcl << " " << p.ecl << " ";
    o << p.pid << " " << p.cid << " ";
    return o;
  }

  bool is_valid() const noexcept {
    return byr.length > 0 && iyr.length > 0 && eyr.length > 0 && hgt.length > 0 && hcl.length > 0 && ecl.length > 0 &&
           pid.length > 0;
  }

  passwort(const char* p1, const char* p2) {
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

int day4(line_view);
} // namespace aoc2020
