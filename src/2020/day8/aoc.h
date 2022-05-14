#pragma once
#include "common.h"

namespace aoc2020 {

enum code_t {
  nop,
  jmp,
  acc,
};

struct code {
  code_t type;
  int value;
  int executed = 0;

  void get_number(const char** pp, int* d) {
    const char* p = *pp;
    int sign = *p == '+' ? 1 : -1;
    p += 1;
    *d = 0;
    while (*p >= '0' && *p <= '9') {
      *d = *d * 10 + *p - '0';
      p++;
    }
    *d *= sign;
    *pp = p;
  }

  code(line_view lv) {
    const char* p = lv.line;
    if (*p == 'a')
      type = acc;
    if (*p == 'n')
      type = nop;
    if (*p == 'j')
      type = jmp;
    while (p < lv.line + lv.length) {
      if (*p == '+' || *p == '-') {
        get_number(&p, &value);
      }
      p++;
    }
  }
};

std::pair<int, int> day8(line_view);

} // namespace aoc2020
