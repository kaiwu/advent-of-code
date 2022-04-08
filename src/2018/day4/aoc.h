#pragma once
#include "common.h"
#include <vector>

namespace aoc2018 {

struct guard {
  int id = 0;
  struct {
    int month;
    int day;
    int hour;
    int minute;
  } timestamp = {0, 0, 0, 0};
  enum {
    on,
    off,
  } status = off;

  std::vector<int> offtime[60];
  std::vector<int> ontime[60];

  void get_number(const char** pp, int* d) {
    const char* p = *pp;
    while (*p >= '0' && *p <= '9') {
      *d = *d * 10 + *p - '0';
      p++;
    }
    *pp = p;
  }

  guard(line_view lv) {
    int* ds[] = {&timestamp.month, &timestamp.day, &timestamp.hour, &timestamp.minute, &id};
    const char* p = lv.line + 6;
    int i{0};
    while (p < lv.line + lv.length) {
      if (*p >= '0' && *p <= '9') {
        get_number(&p, ds[i++]);
        if (i == 4 && *(p + 2) == 'w') {
          status = on;
        }
      }
      p++;
    }
    if (id > 0) {
      status = on;
    }
  };
};

std::pair<int, int> day4(line_view);

} // namespace aoc2018
