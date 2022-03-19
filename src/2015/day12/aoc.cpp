#include "aoc.h"

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

int parse_range(line_view s) {
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

int day12(line_view file) { return parse_range(file); }

bool is_red(const char* p) {
  static const char* red = ":\"red";
  for (int i = 0; i < 5; i++) {
    if (p[i] != red[i]) {
      return false;
    }
  }
  return true;
}

// {{}...{}...{}}
void fix_range(const char* p, const char** pe) {
  int x = 1;
  while (x > 0) {
    if (*p == '{') {
      x += 1;
    }
    if (*p == '}') {
      x -= 1;
    }
    p++;
  }
  *pe = p;
}

void parse_range(const char* p1, const char* p2, int* total) {
  // const char* p0 = p1;
  const char* p = p1;
  int sub = 0;
  while (p != p2) {
    if (*p == ':' && is_red(p)) {
      sub = 0;
      p1 = p;
      break;
    }
    if (*p == '{') {
      sub += parse_range({p1, p});
      const char* pe = nullptr;
      fix_range(p + 1, &pe);
      parse_range(p + 1, pe, &sub);
      p1 = pe;
      p = pe;
    } else {
      p++;
    }
  }
  if (p > p1) {
    sub += parse_range({p1, p});
  }
  // std::cout << line_view{p0 - 1, p2} << " sub:" << sub << std::endl;
  *total += sub;
}

int day12_part2(line_view file) {
  int total = 0;
  const char* p1 = file.line;
  const char* p = p1;
  while (p != file.line + file.length) {
    if (*p == '{') {
      const char* pe = nullptr;
      fix_range(p + 1, &pe);
      total += parse_range({p1, p});
      parse_range(p + 1, pe, &total);
      p1 = pe;
      p = pe;
    } else {
      p++;
    }
  }
  if (p > p1) {
    total += parse_range({p1, p});
  }
  return total;
}

} // namespace aoc2015
