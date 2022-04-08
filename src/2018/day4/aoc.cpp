#include "aoc.h"
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace aoc2018 {

std::pair<int, int> mostlikely(guard* g) {
  int minute[60] = {0};
  for (int i = 0; i < 60; i++) {
    for (auto ms : g->offtime[i]) {
      for (int j = 0; j < ms; j++) {
        minute[i + j] += 1;
      }
    }
  }
  int most{INT32_MIN};
  int highest{INT32_MIN};
  for (int i = 0; i < 60; i++) {
    if (minute[i] > highest) {
      most = i;
      highest = minute[i];
    }
  }
  return {most, highest};
}

int totaloff(guard* g) {
  int d{0};
  for (int i = 0; i < 60; i++) {
    std::for_each(g->offtime[i].begin(), g->offtime[i].end(), [&d](int x) { d += x; });
  }
  return d;
}

std::pair<int, int> day4(line_view file) {
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
        p->ontime[ontime].push_back(g.timestamp.minute - ontime);
        offtime = g.timestamp.minute;
      }
      if (g.status == guard::on) {
        p->offtime[offtime].push_back(g.timestamp.minute - offtime);
        ontime = g.timestamp.minute;
      }
    }
  }

  struct {
    int off = 0;
    guard* g = nullptr;
  } mostoff;

  struct {
    int minute = 0;
    int times = 0;
    guard* g = nullptr;
  } mostfrequent;

  for (auto& kv : hs) {
    int off = totaloff(kv.second);
    if (mostoff.g == nullptr || mostoff.off < off) {
      mostoff.g = kv.second;
      mostoff.off = off;
    }

    auto p = mostlikely(kv.second);
    if (mostfrequent.g == nullptr || mostfrequent.times < p.second) {
      mostfrequent.g = kv.second;
      mostfrequent.minute = p.first;
      mostfrequent.times = p.second;
    }
  }

  int minute = mostlikely(mostoff.g).first;
  // printf("\n%d: %d at %d\n", mostoff.g->id, mostoff.off, minute);
  return {mostoff.g->id * minute, mostfrequent.g->id * mostfrequent.minute};
}

} // namespace aoc2018
