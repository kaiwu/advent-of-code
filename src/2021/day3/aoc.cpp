#include "aoc.h"
#include <algorithm>
#include <vector>

namespace aoc2021 {

int decimal(const char* p) {
  int d{0};
  while (*p == '0' || *p == '1') {
    d = 2 * d + *p - '0';
    p++;
  }
  return d;
}

std::vector<line_view> filter(const std::vector<line_view>& vs, int i, char c) {
  if (vs.size() == 1) {
    return vs;
  }
  std::vector<line_view> n;
  for (auto& lv : vs) {
    if (*(lv.line + i) == c) {
      n.push_back(lv);
    }
  }
  return n;
}

char most_common(std::vector<line_view>& v, int i, char x) {
  size_t t0{0};
  size_t t1{0};
  for (auto& l : v) {
    if (*(l.line + i) == '1') {
      t1++;
    }
    else {
      t0++;
    }
  }
  return t1 > t0 ? '1' : (t1 < t0 ? '0' : x);
}

char least_common(std::vector<line_view>& v, int i, char x) {
  size_t t0{0};
  size_t t1{0};
  for (auto& l : v) {
    if (*(l.line + i) == '1') {
      t1++;
    }
    else {
      t0++;
    }
  }
  return t1 > t0 ? '0' : (t1 < t0 ? '1' : x);
}

void filter(std::vector<line_view>& v1, std::vector<line_view>& v2, int i) {
  if (i < 12) {
    char c1 = most_common(v1, i, '1');
    char c2 = least_common(v2, i, '0');

    v1 = filter(v1, i, c1);
    v2 = filter(v2, i, c2);
    filter(v1, v2, i + 1);
  }
}

std::pair<int, int> day3(line_view file) {
  char gamma[13] = {0};
  char epsilon[13] = {0};

  int is[12] = {0};
  int total{0};
  std::vector<line_view> vs;
  per_line(file, [&is, &total, &vs](line_view lv) {
    vs.push_back(lv);
    for (int i = 0; i < 12; i++) {
      if (*(lv.line + i) == '1') {
        is[i] += 1;
      }
    }
    total += 1;
    return true;
  });

  for (int i = 0; i < 12; i++) {
    if (is[i] > total / 2) {
      gamma[i] = '1';
      epsilon[i] = '0';
    } else {
      gamma[i] = '0';
      epsilon[i] = '1';
    }
  }

  auto v1{vs};
  auto v2{vs};
  filter(v1, v2, 0);

  int p1 = decimal(gamma) * decimal(epsilon);
  int p2 = decimal(v1[0].line) * decimal(v2[0].line);
  return {p1, p2};
}

} // namespace aoc2021
