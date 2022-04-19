#include "aoc.h"
#include "../day5/aoc.h"
#include <set>

namespace aoc2019 {

void find_max(int* is, int i, std::set<int>& ns, int* max, const std::vector<int>& codes) {
  if (i == 10) {
    set_computer(&is[i - 2]);
    int n = run_computer(codes);
    if (n > *max) {
      *max = n;
    }
  } else {
    for (int x : {0, 1, 2, 3, 4}) {
      if (ns.find(x) != ns.end()) {
        continue;
      } else {
        is[i] = x;
        if (i > 0) {
          set_computer(&is[i - 2]);
          is[i + 1] = run_computer(codes);
        }
        ns.insert(x);
        find_max(is, i + 2, ns, max, codes);
        ns.erase(x);
      }
    }
  }
}

static void get_number(const char** pp, int* d) {
  const char* p = *pp;
  int sign = 1;
  if (*p == '-') {
    sign = -1;
    p++;
  }
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *d *= sign;
  *pp = p;
}

int day7(line_view file) {
  int max{INT32_MIN};
  int is[10] = {0};
  std::set<int> ns;
  std::vector<int> codes;
  const char* p = file.line;
  while (p < file.line + file.length) {
    if ((*p >= '0' && *p <= '9') || *p == '-') {
      int d{0};
      get_number(&p, &d);
      codes.push_back(d);
    }
    p++;
  }
  find_max(is, 0, ns, &max, codes);
  return max;
}
} // namespace aoc2019
