#include "aoc.h"
#include <algorithm>

namespace aoc2015 {

int count_vowels(line_view lv, const char* vowels) {
  ascii_count ac{lv};
  int total = 0;
  per_char(vowels, [&ac, &total](char c) {
    total += ac[c];
    return true;
  });
  return total;
}

bool is_nice(line_view lv, int repeated) {
  const char* p = lv.line;
  while (p + repeated <= lv.line + lv.length) {
    if (is_repeated(p, p + repeated)) {
      return true;
    } else {
      p++;
    }
  }
  return false;
}

bool is_nice(line_view lv, const char* disallowed[], size_t size) {
  return not std::any_of(disallowed, disallowed + size, [&lv](const char* s) -> bool { return lv.contains(s); });
}

int day5(line_view file) {
  int total = 0;
  const char* subs[] = {"ab", "cd", "pq", "xy"};
  per_line(file, [&subs, &total](line_view lv) {
    auto b1 = count_vowels(lv, "aeiou") >= 3;
    auto b2 = is_nice(lv, 2);
    auto b3 = is_nice(lv, subs, ARRAY_SIZE(subs));
    if (b1 && b2 && b3) {
      total += 1;
    }
    return true;
  });
  return total;
}

} // namespace aoc2015
