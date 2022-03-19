#include "aoc.h"
#include <stack>

namespace aoc2015 {

int get_number(const char* p1, const char* p2) {
  int sign = *(p1 - 1) == '-' ? -1 : 1;
  int d{0};
  while (p1 != p2) {
    d = d * 10 + *p1 - '0';
    p1++;
  }
  return sign * d;
}

int parse_day12(line_view s) {
  int total = 0;
  const char* p1 = s.line;
  const char* p2 = p1;
  bool to_parse = false;
  while (p2 < s.line + s.length) {
    if (*p2 >= '0' && *p2 <= '9') {
      if (!to_parse) {
        p1 = p2;
        to_parse = !to_parse;
      }
    } else {
      if (to_parse) {
        total += get_number(p1, p2);
        to_parse = !to_parse;
      }
    }
    p2++;
  }
  if (to_parse) {
    total += get_number(p1, p2);
  }
  return total;
}

int day12(line_view file) { return parse_day12(file); }

struct day12_object {
  const char* p1;

  int fold(const char* p2) {
    line_view lv{p1, p2};
    const char* p = lv.contains("red");
    return (p != nullptr) ? 0 : parse_day12(lv);
  }
};

// {{x}   x} = 0
// {{x} ...} = ...
// {{...} x} = 0
// {{...} .} = ... + .
int day12_part2(line_view file) {
  int total = 0;
  std::stack<day12_object> os;
  std::stack<int> is;
  const char* p = file.line;
  const char* p1 = p;
  while (p < file.line + file.length) {
    if (*p == '{') {
      if (os.empty()) {
        total += parse_day12({p1, p});
        p1 = p;
      }
      os.push({p});
    }
    if (*p == '}') {
      auto o = os.top();
      is.push(o.fold(p));
      os.pop();
      if (os.empty()) {
        while (!is.empty()) {
          total += is.top();
          is.pop();
        }
        p1 = p;
      } else {
        auto& oo = os.top();
        oo.p1 = p;
      }
    }
    p++;
  }
  total += parse_day12({p1, p});
  return total;
}

} // namespace aoc2015
