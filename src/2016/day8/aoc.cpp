#include "aoc.h"

namespace aoc2016 {

static void get_number(const char** pp, int* d) {
  const char* p = *pp;
  *d = 0;
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *pp = p;
}

static void get_number(const char* p1, const char* p2, int* ds) {
  int index{0};
  while (p1 < p2) {
    if (*p1 >= '0' && *p1 <= '9') {
      get_number(&p1, &ds[index++]);
    }
    p1++;
  }
}

int day8(line_view file) {
  grid<50, 6> g;
  per_line(file, [&g](line_view lv) {
    const char* p = lv.line;
    int ds[2] = {0};
    get_number(p, p + lv.length, ds);
    if (p[1] == 'e') {
      g.set(ds[0], ds[1]);
    }
    if (p[1] == 'o' && p[7] == 'c') {
      g.rotate_v(ds[0], ds[1]);
    }
    if (p[1] == 'o' && p[7] == 'r') {
      g.rotate_h(ds[0], ds[1]);
    }
    // g.print();
    return true;
  });
  return g.count();
}

} // namespace aoc2016
