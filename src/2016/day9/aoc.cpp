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

static void check0(int t, const char* p1, const char* p2, size_t* t1) {
  size_t x{0};
  while (p1 < p2) {
    if (*p1 == '(') {
      int d[2] = {0};
      int i = 0;
      while (*p1 != ')') {
        if (*p1 >= '0' && *p1 <= '9') {
          get_number(&p1, d + i++);
        }
        if (*p1 == '(' || *p1 == 'x') {
          p1++;
        }
      }
      check0(d[1], p1 + 1, p1 + d[0] + 1, &x);
      p1 += d[0] + 1;
    } else {
      p1++;
      x++;
    }
  }
  *t1 += t * x;
}

static void check(const char** pp, int* t0, size_t* t1) {
  int d[2] = {0};
  const char* p = *pp;
  int i = 0;
  while (*p != ')') {
    if (*p >= '0' && *p <= '9') {
      get_number(&p, d + i++);
    }
    if (*p == '(' || *p == 'x') {
      p++;
    }
  }
  *t0 += d[1] * d[0];
  check0(d[1], p + 1, p + d[0] + 1, t1);
  *pp = p + d[0] + 1;
}

std::pair<int, size_t> day9(line_view file) {
  int t0{0};
  size_t t1{0};

  const char* p1 = file.line;
  const char* p2 = p1 + file.length;

  while (p1 < p2) {
    if (*p1 == '(') {
      check(&p1, &t0, &t1);
    } else {
      if (*p1 != ' ' && *p1 != '\n') {
        t0++;
        t1++;
      }
      p1++;
    }
  }
  return {t0, t1};
}

} // namespace aoc2016
