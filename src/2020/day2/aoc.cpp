#include "aoc.h"

namespace aoc2020 {

int count(char c, const char* p) {
  int total{0};
  while (*p >= 'a' && *p <= 'z') {
    if (*p == c) {
      total++;
    }
    p++;
  }
  return total;
}

void minmax(int* min, int* max, const char* p1, const char* p2) {
  int* p = min;
  while (p1 < p2) {
    if (*p1 >= '0' && *p1 <= '9') {
      *p = *p * 10 + *p1 - '0';
    } else {
      p = max;
    }
    p1++;
  }
}

// 8-10 g: gggggggggg
bool is_valid1(line_view lv) {
  const char* p = lv.contains(":");
  int n = count(*(p - 1), p + 2);
  int min{0};
  int max{0};
  minmax(&min, &max, lv.line, p - 2);
  return n >= min && n <= max;
}

bool is_valid2(line_view lv) {
  const char* p = lv.contains(":");
  int p1{0};
  int p2{0};
  minmax(&p1, &p2, lv.line, p - 2);
  bool b1 = *(p + 1 + p1) == *(p - 1);
  bool b2 = *(p + 1 + p2) == *(p - 1);
  return int(b1) + int(b2) == 1;
}

std::pair<int, int> day2(line_view file) {
  int total0{0};
  int total1{0};
  per_line(file, [&total0, &total1](line_view lv) {
    total0 += int(is_valid1(lv));
    total1 += int(is_valid2(lv));
    return true;
  });
  return {total0, total1};
}

} // namespace aoc2020
