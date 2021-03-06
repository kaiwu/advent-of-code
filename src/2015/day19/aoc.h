#pragma once

#include "common.h"
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace aoc2015 {

struct replacement {
  line_view from;
  line_view to;
};

struct molecule {
  std::vector<replacement> replacements;
  std::map<line_view, std::vector<line_view>> transfers;
  std::map<line_view, line_view> backwards;
  line_view original;

  struct change {
    size_t i;
    replacement c;
  };

  struct pattern {
    int depth;
    line_view lv;
  };

  // r.to -> r.from at p
  line_view replace(line_view lv, const replacement& r, const char* p) const noexcept {
    size_t len = lv.length + r.to.length - r.from.length;
    char* s = (char*)malloc(len);
    memset(s, 0x0, len);
    const char* ps[] = {lv.line, p, p + r.from.length, lv.line + lv.length};
    char* x = s;
    for (size_t i = 0; i < 3; i++) {
      if (i != 1) {
        const char* p1 = ps[i];
        const char* p2 = ps[i + 1];
        // std::cout << line_view{p1, p2} << std::endl;
        memcpy(x, p1, p2 - p1);
        x += (p2 - p1);
      } else {
        const char* p1 = r.to.line;
        const char* p2 = r.to.line + r.to.length;
        // std::cout << line_view{p1, p2} << std::endl;
        memcpy(x, p1, p2 - p1);
        x += (p2 - p1);
      }
    }
    return {s, len};
  }

  line_view deduce(line_view lv, int* step) {
    if (transfers.find(lv) == transfers.end()) {
      auto it = backwards.find(lv);
      if (it != backwards.end()) {
        *step += 1;
        return it->second;
      } else {
        const char* p1 = lv.line;
        const char* p2 = lv.line + lv.length;
        const char* p = p1 + 1;
        while (p < p2) {
          auto jt = backwards.find({p1, p});
          if (jt != backwards.end()) {
            replacement r{{p1, p}, jt->second};
            line_view n = replace(lv, r, p1);
            *step += 1;
            return deduce(n, step);
          } else {
            p++;
          }
        }
      }
    }
    return lv;
  }

  line_view deduce(line_view lv, const char* p, int* step) {
    const char* p1 = p;
    do {
      p--;
    } while (backwards.find({p, p1}) == backwards.end());
    auto it = backwards.find({p, p1});
    *step += 1;
    return replace(lv, {it->first, it->second}, p);
  }

  void parse_y(line_view lv, std::vector<line_view>& ys) {
    const char* p1 = lv.line;
    const char* p2 = lv.line + lv.length;
    while (p1 < p2) {
      line_view x{p1, p2};
      const char* p = x.contains("Y");
      if (p != nullptr) {
        ys.push_back({p1, p});
        p1 = p + 1;
      } else {
        break;
      }
    }
    ys.push_back({p1, p2});
  }

  //...Rn..Ar
  void parse_pattern(line_view lv, int depth, std::vector<pattern>& ps, const char** a) {
    const char* p1 = lv.line;
    const char* p2 = lv.line + lv.length;
    const char* p = p1;
    while (p < p2) {
      if (*p == 'R') {
        parse_pattern({p + 2, p2}, depth + 1, ps, a);
        p = *a + 2;
        continue;
      }
      if (*p == 'A' && *(p + 1) == 'r') {
        // ps.push_back({depth, {p1 - 2, p + 2}});
        ps.push_back({depth, {p1, p}});
        *a = p;
        return;
      }
      p++;
    }
    ps.push_back({depth, {p1, p}});
  }

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

  std::string apply(const change& c) const noexcept {
    int len = original.length + c.c.to.length - c.c.from.length + 1;
    // int len = original.length + 1;
    char* s = (char*)malloc(len);
    memset(s, 0x0, len);
    // const char* ps[] = {original.line, c.c.from.line, c.c.from.line + c.c.from.length, original.line +
    // original.length};
    const char* ps[] = {original.line, c.c.from.line, c.c.from.line + c.c.from.length, original.line + original.length};
    char* p = s;
    for (size_t i = 0; i < 3; i++) {
      if (i != 1) {
        const char* p1 = ps[i];
        const char* p2 = ps[i + 1];
        // std::cout << line_view{p1, p2} << std::endl;
        memcpy(p, p1, p2 - p1);
        p += (p2 - p1);
      } else {
        const char* p1 = c.c.to.line;
        const char* p2 = c.c.to.line + c.c.to.length;
        // std::cout << line_view{p1, p2} << std::endl;
        memcpy(p, p1, p2 - p1);
        p += (p2 - p1);
      }
    }
    return std::string(s);
  }

  int distinct(const std::vector<change>& vc) const noexcept {
    std::set<std::string> ss;
    for (auto& c : vc) {
      // std::cout << c.i << ": " << original << " " << (c.c.from.line - original.line) << " " << c.c.to << std::endl;
      auto s = apply(c);
      // std::cout << "<" << s.length() << ":" << s << ">" << std::endl;
      ss.insert(s);
    }
    return ss.size();
  }

  int distinct(const std::map<int, std::vector<change>>& vr) const noexcept {
    int d{0};
    for (auto& kv : vr) {
      d += distinct(kv.second);
    }
    return d;
  }

  void step(int i) const noexcept {
    while (i-- > 0) {
      std::cout << "\t";
    }
  }

  // exponential down
  void deduct(line_view lv, int steps, int* shortest) const noexcept {
    if (lv == "e") {
      if (*shortest > steps) {
        *shortest = steps;
      }
      return;
    } else {
      for (auto& r : replacements) {
        const char* p1 = lv.line;
        const char* p2 = lv.line + lv.length;
        while (p1 < p2) {
          line_view v{p1, p2};
          const char* p = v.contains(r.to);
          if (p != nullptr) {
            line_view n = replace(lv, {r.to, r.from}, p);
            // step(steps);
            // std::cout << lv << " " << p - lv.line << " " << r.to << " -> " << n << std::endl;
            deduct(n, steps + 1, shortest);
            delete n.line;
            p1 = p + r.to.length;
          } else {
            break;
          }
        }
      }
    }
  }

  line_view replace(line_view lv, int* steps) const noexcept {
    for (auto kv : backwards) {
      const char* r = kv.first.contains("Rn");
      const char* p = lv.contains(kv.first);
      if (r != nullptr && p != nullptr) {
        *steps += 1;
        line_view ln = replace(lv, {kv.first, kv.second}, p);
        return replace(ln, steps);
      }
    }
    return lv;
  }

  void parse(line_view lv, std::vector<line_view>& ms) const noexcept {
    const char* p1 = lv.line;
    const char* p2 = lv.line + lv.length;
    while (p1 < p2) {
      if (transfers.find({p1, 1}) != transfers.end()) {
        ms.push_back({p1, 1});
        p1 += 1;
        continue;
      }
      if (p1 < p2 - 1 && transfers.find({p1, 2}) != transfers.end()) {
        ms.push_back({p1, 2});
        p1 += 2;
        continue;
      }
      p1++;
    }
  }

  void sort() {
    for (auto& kv : transfers) {
      std::sort(kv.second.begin(), kv.second.end());
    }
  }

  // exponential up
  void transfer(line_view lv, int steps, int* shortest) {
    if (lv.length > original.length) {
      return;
    }
    if (lv == original) {
      printf("e: %d\n", steps);
      if (*shortest > steps) {
        *shortest = steps;
      }
    } else {
      std::vector<line_view> ms;
      parse(lv, ms);
      for (auto& from : ms) {
        for (auto& to : transfers[from]) {
          line_view next = replace(lv, {from, to}, from.line);
          transfer(next, steps + 1, shortest);
          delete next.line;
        }
      }
    }
  }

  void parse(line_view lv) {
    const char* p = lv.contains("=>");
    if (p != nullptr) {
      line_view k{lv.line, p - 1};
      line_view v{p + 3, lv.line + lv.length - 1};
      replacements.push_back({k, v});
      transfers[k].push_back(v);
      backwards.insert({v, k});
    } else {
      if (lv.length > 1) {
        original = {lv.line, lv.line + lv.length - 1};
      }
    }
  }
}; // namespace aoc2015

std::pair<int, int> day19(line_view);

} // namespace aoc2015
