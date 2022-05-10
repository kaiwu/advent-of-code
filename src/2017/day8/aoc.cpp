#include "aoc.h"
#include <unordered_map>

namespace aoc2017 {

int largest(const std::unordered_map<line_view, int>& rs) {
  int max{INT32_MIN};
  for (auto& kv : rs) {
    if (kv.second > max) {
      max = kv.second;
    }
  }
  return max;
}

static void get_number(const char** pp, int* d) {
  const char* p = *pp;
  *d = 0;
  int sign = 1;
  if (*p == '-') {
    sign = -1;
    p++;
  }
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *d = *d * sign;
  *pp = p;
}

line_view get_label(const char** pp) {
  const char* p = *pp;
  const char* p1 = p;
  while (*p != ' ') {
    p++;
  }
  *pp = p;
  return {p1, p};
}

static int inc(int x, int i) { return x + i; }
static int dec(int x, int i) { return x - i; }
static bool condition_met(line_view cond, int x, int i) {
  if (*cond.line == '=') {
    return x == i;
  }
  if (*cond.line == '!') {
    return x != i;
  }
  bool bs[] = {x > i, x < i, x >= i, x <= i};
  return bs[size_t(*cond.line == '<') + (cond.length & 2)];
}

typedef int (*op)(int, int);
std::pair<int, int> day8(line_view file) {
  std::unordered_map<line_view, int> registers;
  int max{INT32_MIN};
  per_line(file, [&registers, &max](line_view lv) {
    const char* p = lv.line;
    line_view v1 = get_label(&p);
    op f = p[1] == 'd' ? dec : inc;

    p += 5;
    int d1{0};
    get_number(&p, &d1);

    p += 4;
    line_view v2 = get_label(&p);

    p += 1;
    line_view condition = get_label(&p);

    p += 1;
    int d2{0};
    get_number(&p, &d2);
    if (condition_met(condition, registers[v2], d2)) {
      registers[v1] = f(registers[v1], d1);
      if (registers[v1] > max) {
        max = registers[v1];
      }
    }
    return true;
  });
  return {largest(registers), max};
}

} // namespace aoc2017
