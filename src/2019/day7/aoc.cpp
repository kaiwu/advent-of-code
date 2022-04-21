#include "aoc.h"
#include "../day5/aoc.h"
#include <algorithm>
#include <set>

namespace aoc2019 {

void find_max(int* is, int i, std::set<int>& ns, int* max, const std::vector<int>& codes) {
  if (i == 10) {
    set_computer(&is[i - 2]);
    int n = run_computer(codes);
    // printf("%d %d %d %d %d -> %d\n", is[0], is[2], is[4], is[6], is[8], n);
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

std::pair<int, int> day7(line_view file) {
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
  int m1{INT32_MIN};
  int is1[10] = {0};
  std::set<int> ns1;
  find_max(is1, 0, ns1, &m1, codes);

  for (int i : {5, 6, 7, 8, 9}) {
    int is2[10] = {0};
    is2[0] = i;
    is2[1] = 33;
    set_computer(is2);
    std::vector<int> outputs;
    run_computer(0, codes, outputs, nullptr);
    std::for_each(outputs.begin(), outputs.end(), [](int x) { printf("%d ", x); });
    printf("\n");
  }

  return {m1, 0};
}
} // namespace aoc2019
