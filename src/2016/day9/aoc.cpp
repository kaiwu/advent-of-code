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

static void check(const char** pp, int* t) {
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
  p += d[0];
  *t += d[1] * d[0];
  *pp = p;
}

int day9(line_view file) {
  int t0{0};

  const char* p1 = file.line;
  const char* p2 = p1 + file.length - 1;
  const char* p = p1;

  while (p < p2) {
    if (*p == '(') {
      check(&p, &t0);
      p++;
    } else {
      if (*p != ' ') {
        t0++;
      }
      p++;
    }
  }
  return t0;
}

} // namespace aoc2016
