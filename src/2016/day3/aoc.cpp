#include "aoc.h"

namespace aoc2016 {

void get_number(const char** pp, int* d) {
  const char* p = *pp;
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *pp = p;
}

void get_sides(line_view lv, int is[]) {
  const char* p = lv.line;
  size_t i{0};
  while (p < lv.line + lv.length) {
    if (*p >= '0' && *p <= '9') {
      get_number(&p, &is[i++]);
    }
    p++;
  }
}

int is_triangle(int is[]) {
  auto b1 = is[0] + is[1] > is[2];
  auto b2 = is[0] + is[2] > is[1];
  auto b3 = is[1] + is[2] > is[0];
  return int(b1 && b2 && b3);
}

int has_triangle(int is[]) {
  auto b1 = is[0] + is[3] > is[6];
  auto b2 = is[0] + is[6] > is[3];
  auto b3 = is[3] + is[6] > is[0];

  auto b4 = is[1] + is[4] > is[7];
  auto b5 = is[1] + is[7] > is[4];
  auto b6 = is[4] + is[7] > is[1];

  auto b7 = is[2] + is[5] > is[8];
  auto b8 = is[2] + is[8] > is[5];
  auto b9 = is[5] + is[8] > is[2];

  return int(b1 && b2 && b3) + int(b4 && b5 && b6) + int(b7 && b8 && b9);
}

std::pair<int, int> day3(line_view file) {
  int t0{0};
  int t1{0};
  size_t i{0};
  const char* p = file.line;
  per_line(file, [&t0, &t1, &i, &p](line_view lv) {
    i++;
    if (i % 3 == 0) {
      int xs[9] = {0};
      get_sides(line_view{p, lv.line + lv.length}, xs);
      t1 += has_triangle(xs);
      p = lv.line + lv.length + 1;
    }
    int is[3] = {0};
    get_sides(lv, is);
    t0 += is_triangle(is);
    return true;
  });
  return {t0, t1};
}

} // namespace aoc2016
