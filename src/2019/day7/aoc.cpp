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

struct check_t {
  int* a;
  int* b;
};

bool interrupt(size_t i, std::vector<int>& outputs, void* out) {
  if (outputs.size() > 0) {
    check_t* x = (check_t*)out;
    if (x->b - x->a == 12) {
      *(x->b + 2) = i;
      *(x->a + 1) = outputs[0];
    } else {
      *(x->b + 2) = i;
      *(x->b + 4) = outputs[0];
    }
    return true;
  }
  return false;
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

  auto print = [](int* is) {
    for (size_t i = 0; i < 15; i++) {
      printf("%d ", is[i]);
    }
    printf("\n");
  };

  auto copy = [](int* s1, int* s2) {
    for (int i = 0; i < 15; i++) {
      s1[i] = s2[i];
    }
  };

  auto equal = [](int* s1, int* s2) -> bool {
    for (int i = 0; i < 15; i++) {
      if (s1[i] != s2[i]) {
        return false;
      }
    }
    return true;
  };

  int is2[15] = {9, 0, 0, 7, 0, 0, 8, 0, 0, 5, 0, 0, 6, 0, 0};
  int is3[15] = {0};
  std::vector<int> cs[] = {codes, codes, codes, codes, codes};
  bool stop{false};
  while (!stop) {
    copy(is3, is2);
    for (size_t i = 0; i < ARRAY_SIZE(is2); i += 3) {
      std::vector<int> outputs;
      check_t chk{is2, &is2[i]};
      is2[i + 2] == 0 ? set_computer(&is2[i]) : set_computer(&is2[i + 1]);
      run_computer(is2[i + 2], cs[i / 3], outputs, interrupt, &chk);
    }
    stop = equal(is3, is2);
    print(is2);
  }
  printf("%d\n", is2[1]);

  return {m1, 0};
}
} // namespace aoc2019
