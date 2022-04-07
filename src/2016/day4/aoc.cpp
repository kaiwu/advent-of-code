#include "aoc.h"
#include <algorithm>
#include <string.h>
#include <vector>

namespace aoc2016 {

struct ccount {
  char c;
  int count;

  bool operator<(const ccount& other) const noexcept {
    return count > other.count ? true : (count < other.count ? false : c < other.c);
  };
};

unsigned char shift(unsigned char c, int times) {
  if (c == '-') {
    return ' ';
  }
  times %= 26;
  c += times;
  if (c > 'z') {
    c = 'a' + c - 'z' - 1;
  }
  return c;
}

bool is_real_room(line_view lv, int* id, char names[]) {
  const char* p = lv.line;
  while (!(*p >= '0' && *p <= '9')) {
    p++;
  }
  const char* p0 = p;

  ascii_count ac{{lv.line, p}};
  std::vector<ccount> cc;
  for (char i = 'a'; i <= 'z'; i++) {
    cc.push_back({i, ac.count[int(i)]});
  }
  std::sort(cc.begin(), cc.end());

  while (*p >= '0' && *p <= '9') {
    *id = *id * 10 + *p - '0';
    p++;
  }
  int x{0};
  for (const char* p1 = lv.line; p1 != p0; p1++) {
    names[x++] = shift(*p1, *id);
  }
  for (int i = 0; i < 5; i++) {
    if (*(p + i + 1) != cc[i].c) {
      return false;
    }
  }
  return true;
}

std::pair<int, int> day4(line_view file) {
  int total{0};
  int pole_id{0};
  per_line(file, [&total, &pole_id](line_view lv) {
    int id{0};
    char names[100] = {0};
    if (is_real_room(lv, &id, names)) {
      // printf("%d %s\n", id, names);
      if (strstr(names, "northpole")) {
        pole_id = id;
      }
      total += id;
    }
    return true;
  });
  return {total, pole_id};
}

} // namespace aoc2016
