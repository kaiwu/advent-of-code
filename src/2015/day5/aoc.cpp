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
  while (p + repeated < lv.line + lv.length) {
    if (is_repeated(p, p + repeated)) {
      return true;
    } else {
      p++;
    }
  }
  return false;
}

bool is_nice(line_view lv, const char* disallowed[]) {
  size_t size = sizeof(disallowed) / sizeof(*disallowed);
  if (std::any_of(disallowed, disallowed + size, [&lv](const char* s) -> bool { return lv.contains(s); })) {
    return false;
  }
  return true;
}

/*
int day5(line_view) {}
*/

} // namespace aoc2015
