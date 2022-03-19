#pragma once

#include "common.h"
#include <map>
#include <set>
#include <vector>

namespace aoc2015 {

struct guest {
  line_view name;
  std::map<guest*, int> points;

  int point(guest* other) {
    auto it = points.find(other);
    return it != points.end() ? it->second : 0;
  }
};

struct party {
  std::vector<guest*> guests;

  guest* the(line_view lv) {
    for (auto g : guests) {
      if (g->name == lv) {
        return g;
      }
    }
    guests.emplace_back(new guest{lv, {}});
    return guests.back();
  }

  int happiness(std::vector<guest*> gs) const noexcept {
    int h = 0;
    int size = gs.size();
    for (int i = 0; i < size; i++) {
      guest* g1 = gs[i];
      guest* g2 = i < size - 1 ? gs[i + 1] : gs[0];
      h += g1->point(g2);
      h += g2->point(g1);
    }
    return h;
  }

  int happiness(const char* p) {
    int h{0};
    while (*p != ' ') {
      h = h * 10 + *p - '0';
      p++;
    }
    return h;
  }

  // backtrace
  typedef std::vector<guest*>* arrange_t;
  typedef std::vector<std::vector<guest*>> combo_t;
  void arrange(guest* g, std::set<guest*>& gs, arrange_t arrangement, combo_t& combos) const noexcept {
    if (arrangement->size() == guests.size()) {
      combos.push_back(*arrangement);
      return;
    }
    for (auto& kv : g->points) {
      if (gs.find(kv.first) != gs.end()) {
        continue;
      } else {
        gs.insert(kv.first);
        arrangement->push_back(kv.first);
        arrange(kv.first, gs, arrangement, combos);
        arrangement->pop_back();
        gs.erase(kv.first);
      }
    }
  }

  std::pair<int, int> arrange() const noexcept {
    combo_t combos;
    for (auto g : guests) {
      arrange_t arrangement = new std::vector<guest*>;
      std::set<guest*> gs;
      arrange(g, gs, arrangement, combos);
      break;
    }

    int hmax = INT32_MIN;
    int hmin = INT32_MAX;
    for (auto c : combos) {
      int h = happiness(c);
      /*
      std::cout << "[" << h << ":";
      for (auto x : c) {
        std::cout << x->name << " -> ";
      }
      std::cout << "]" << std::endl;
      */
      if (hmax < h) {
        hmax = h;
      }
      if (hmin > h) {
        hmin = h;
      }
    }
    return {hmin, hmax};
  }

  void parse(line_view lv) {
    const char* p = lv.line;
    const char* p1 = lv.contains("would");
    const char* p2 = lv.contains("to");
    guest* g1 = the({p, p1 - 1});
    guest* g2 = the({p2 + 3, p + lv.length - 2});
    int point = happiness(p1 + 11);
    if (*(p1 + 6) == 'l') {
      point = -point;
    }
    // std::cout << g1->name << " -> " << g2->name << ":" << point << std::endl;
    g1->points.insert({g2, point});
  }

  void add(const char* x, int h) {
    guest* ng = new guest{x, {}};
    for (auto g : guests) {
      g->points.insert({ng, h});
      ng->points.insert({g, h});
    }
    guests.push_back(ng);
  }
};

std::pair<int, int> day13(line_view file, const char* = nullptr);

} // namespace aoc2015
