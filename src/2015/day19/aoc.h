#pragma once

#include "common.h"
#include <map>
#include <vector>

namespace aoc2015 {

struct replacement {
  line_view from;
  line_view to;
};

struct molecule {
  std::vector<replacement> replacements;
  line_view original;

  struct change {
    size_t i;
    replacement c;
  };

  void check(size_t i, replacement r, std::map<int, std::vector<change>>& vr) const noexcept {
    const char* p1 = original.line;
    const char* p2 = original.line + original.length;
    do {
      line_view lv = line_view{p1, p2};
      const char* p = lv.contains(r.from);
      // std::cout << lv << ": " << r.from << " -> " << r.to << std::endl;
      if (p != nullptr) {
        vr[r.to.length - r.from.length].push_back({i, {line_view{p, r.from.length}, r.to}});
        p1 = p + r.from.length;
      } else {
        break;
      }
    } while (p1 < p2);
  }

  void check(std::map<int, std::vector<change>>& vr) const noexcept {
    for (size_t i = 0; i < replacements.size(); i++) {
      check(i, replacements[i], vr);
    }
  }

  int distinct(const std::vector<change>& vc) const noexcept {
    for (auto& c : vc) {
      std::cout << c.i << ": " << original << " " << (c.c.from.line - original.line) << " " << c.c.to << std::endl;
    }
    return 0;
  }

  int distinct(const std::map<int, std::vector<change>>& vr) const noexcept {
    int d{0};
    for (auto& kv : vr) {
      d += distinct(kv.second);
    }
    return d;
  }

  void parse(line_view lv) {
    const char* p = lv.contains("=>");
    if (p != nullptr) {
      replacements.push_back({{lv.line, p - 1}, {p + 3, lv.line + lv.length - 1}});
    } else {
      if (lv.length > 1) {
        original = {lv.line, lv.line + lv.length - 1};
      }
    }
  }
};

int day19(line_view);

} // namespace aoc2015
