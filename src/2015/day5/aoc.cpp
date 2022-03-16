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

bool is_interleaved(line_view lv) {
  const char* p = lv.line;
  while (p + 3 <= lv.line + lv.length) {
    if (*p == *(p + 2)) {
      return true;
    } else {
      p++;
    }
  }
  return false;
}

bool has_no_overlap_pair(line_view lv) {
  const char* p1 = lv.line;
  const char* p2 = lv.line + lv.length;
  while (p1 + 2 <= p2) {
    line_view h{p1, 2};
    line_view t{p1 + 2, p2};
    if (t.contains(h) != nullptr) {
      return true;
    } else {
      p1++;
    }
  }
  return false;
}

bool is_nice(line_view lv, const char* disallowed[], size_t size) {
  return std::all_of(disallowed, disallowed + size, [&lv](const char* s) -> bool { return lv.contains(s) == nullptr; });
}

std::pair<int,int> day5(line_view file) {
  int total0 = 0;
  int total1 = 0;
  const char* subs[] = {"ab", "cd", "pq", "xy"};
  per_line(file, [&subs, &total0, &total1](line_view lv) {
    auto b1 = count_vowels(lv, "aeiou") >= 3;
    auto b2 = is_nice(lv, 2);
    auto b3 = is_nice(lv, subs, ARRAY_SIZE(subs));
    auto b4 = is_interleaved(lv);
    auto b5 = has_no_overlap_pair(lv);
    if (b1 && b2 && b3) {
      total0 += 1;
    }
    if (b4 && b5) {
      total1 += 1;
    }
    return true;
  });
  return {total0, total1};
}

} // namespace aoc2015
