#include "aoc.h"
#include <string.h>
#include <string>
#include <vector>

namespace aoc2019 {

bool smaller(const char* s1, const char* s2) { return std::atoi(s1) < std::atoi(s2); }

bool two_identical(const char* s) {
  const char* n = s + strlen(s);
  while (s < n - 1) {
    if (*s == *(s + 1)) {
      return true;
    }
    s++;
  }
  return false;
}

bool two_identical_plus(const char* s) {
  auto is_right = [s](int i, int j) -> bool {
    bool b1 = s[i] == s[j];
    bool b2 = i > 0 ? s[i] != s[i - 1] : true;
    bool b3 = j < 5 ? s[j] != s[j + 1] : true;
    return b1 && b2 && b3;
  };
  for (int i = 0; i < 5; i++) {
    if (is_right(i, i + 1)) {
      return true;
    }
  }
  return false;
}

typedef bool (*identical_f)(const char*);

void next(size_t i, size_t j, char p[], const char* low, const char* high, int* c1, int* c2) {
  static char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  if (i == strlen(high)) {
    if (smaller(p, high) && smaller(low, p)) {
      *c1 += int(two_identical(p));
      *c2 += int(two_identical_plus(p));
    }
  } else {
    for (size_t x = j; x < ARRAY_SIZE(digits); x++) {
      p[i] = digits[x];
      next(i + 1, x, p, low, high, c1, c2);
    }
  }
}

std::pair<int, int> day4(const char* low, const char* high) {
  char pass[7] = {0};
  int c1{0};
  int c2{0};
  next(0, 0, pass, low, high, &c1, &c2);
  return {c1, c2};
}

} // namespace aoc2019
