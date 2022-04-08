#include "aoc.h"
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace aoc2018 {

int day4(line_view file) {
  std::vector<guard> gs;
  per_line(file, [&gs](line_view lv) {
    gs.emplace_back(lv);
    return true;
  });

  std::sort(gs.begin(), gs.end(), [](const guard& g1, const guard& g2) {
    int ts[] = {g1.timestamp.month, g1.timestamp.day, g1.timestamp.hour, g1.timestamp.minute,
                g2.timestamp.month, g2.timestamp.day, g2.timestamp.hour, g2.timestamp.minute};
    for (int i = 0; i < 4; i++) {
      if (ts[i] < ts[i + 4]) {
        return true;
      }
      if (ts[i] > ts[i + 4]) {
        return false;
      }
    }
    return false;
  });
  // std::for_each(gs.begin(), gs.end(), [](const guard& g) {
  //   printf("%02d-%02d %02d:%02d #%d %s\n", g.timestamp.month, g.timestamp.day, g.timestamp.hour, g.timestamp.minute,
  //          g.id, g.status == guard::on ? "on" : "off");
  // });

  std::unordered_map<int, guard*> hs;
  guard* p{nullptr};
  int ontime{0};
  int offtime{0};
  for (auto& g : gs) {
    if (g.id > 0) {
      auto it = hs.find(g.id);
      if (it != hs.end()) {
        p = it->second;
      } else {
        p = new guard(g);
        hs.insert({g.id, p});
      }
      // 23:49
      ontime = g.timestamp.hour > 0 ? 0 : g.timestamp.minute;
    } else {
      if (g.status == guard::off) {
        p->ontime[ontime] += g.timestamp.minute - ontime;
        offtime = g.timestamp.minute;
      }
      if (g.status == guard::on) {
        p->offtime[offtime] += g.timestamp.minute - offtime;
        ontime = g.timestamp.minute;
      }
    }
  }

  struct {
    int off = 0;
    guard* g = nullptr;
  } mostoff;

  auto totaloff = [](guard* g) {
    int d{0};
    for (int i = 0; i < 60; i++) {
      d += g->offtime[i];
    }
    return d;
  };

  for (auto& kv : hs) {
    int off = totaloff(kv.second);
    printf("%d: %d\n", kv.second->id, off);
    if (mostoff.g == nullptr || mostoff.off < off) {
      mostoff.g = kv.second;
      mostoff.off = off;
    }
  }
  printf("%d: %d\n", mostoff.g->id, mostoff.off);
  return 0;
}

} // namespace aoc2018
