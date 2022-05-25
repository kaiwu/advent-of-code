#include "aoc.h"
#include <stack>

namespace aoc2017 {

static void take(const char* p, std::stack<char>& gs, int* t) {
  if (*p == '{') {
    gs.push(*p);
  }
  if (*p == '}') {
    *t += gs.size();
    gs.pop();
  }
}

static bool is_valid(const char* p, std::stack<char>& g, int* t) {
  if (g.empty()) {
    if (*p == '!') {
      g.push(*p);
    }
    if (*p == '<') {
      g.push(*p);
    }
  } else {
    if (g.top() == '!') {
      g.pop();
    } else {
      *t += 1;
      if (*p == '>') {
        g.pop();
        *t -= 1;
      }
      if (*p == '!') {
        g.push(*p);
        *t -= 1;
      }
    }
  }

  return g.empty();
}

std::pair<int, int> day9(line_view file) {
  int t0{0};
  int t1{0};
  std::stack<char> gs;
  std::stack<char> gv;
  const char* p = file.line;
  while (p < file.line + file.length) {
    if (is_valid(p, gv, &t1)) {
      take(p, gs, &t0);
    }
    p++;
  }
  return {t0, t1};
}

} // namespace aoc2017
