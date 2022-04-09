#include "aoc.h"
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace aoc2021 {

struct bnum {
  int i;
  int v;

  bool operator<(const bnum& b) const noexcept { return v < b.v; }
};

void get_number(const char** pp, int* d) {
  const char* p = *pp;
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *pp = p;
}

struct bingo {
  std::unordered_map<int, int> ns;
  std::vector<bnum> vs;
  void parse(line_view lv) {
    const char* p = lv.line;
    int index{0};
    while (p < lv.line + lv.length) {
      if (*p >= '0' && *p <= '9') {
        int d{0};
        get_number(&p, &d);
        vs.push_back({index++, d});
      }
      p++;
    }
    std::sort(vs.begin(), vs.end());
  }
};

int search(int n, bingo& b) {
  auto it = b.ns.find(n);
  if (it != b.ns.end()) {
    return it->second;
  }
  int left = 0;
  int right = b.vs.size() - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (b.vs[mid].v == n) {
      int i = b.vs[mid].i;
      b.ns.insert({n, i});
      return i;
    } else if (b.vs[mid].v < n) {
      left = mid + 1;
    } else if (b.vs[mid].v > n) {
      right = mid - 1;
    }
  }
  return INT32_MAX;
}

struct board {
  bnum is[25];
  int at;

  board(line_view lv, bingo* b) {
    const char* p = lv.line;
    int index{0};
    while (p < lv.line + lv.length) {
      if (*p >= '0' && *p <= '9') {
        is[index].v = 0;
        get_number(&p, &(is[index].v));
        is[index].i = search(is[index].v, *b);
        index++;
      }
      p++;
    }
    at = bingo_at();
    print();
  }

  void print() const noexcept {
    int i{0};
    for (auto& b : is) {
      // printf("{%02d,%02d}", b.v, b.i);
      printf("{%02d}", b.v);
      if (++i % 5 == 0) {
        printf("\n");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }

  int sum_unmarked() {
    int s{0};
    for (auto& n : is) {
      if (n.i == INT32_MAX) {
        s += n.v;
      }
    }
    return s;
  }

  bool operator<(const board& b) const noexcept { return at < b.at; }
  int bingo_at() const noexcept {
    int b{INT32_MAX};

    auto is_bingo_r = [this](int y) -> int {
      int m{INT32_MIN};
      for (int x : {0, 1, 2, 3, 4}) {
        auto p = is[y * 5 + x].i;
        if (p == INT32_MAX) {
          return INT32_MAX;
        } else {
          if (p > m) {
            m = p;
          }
        }
      }
      return m;
    };

    auto is_bingo_c = [this](int x) -> int {
      int m{INT32_MIN};
      for (int y : {0, 1, 2, 3, 4}) {
        auto p = is[y * 5 + x].i;
        if (p == INT32_MAX) {
          return INT32_MAX;
        } else {
          if (p > m) {
            m = p;
          }
        }
      }
      return m;
    };

    for (int i : {0, 1, 2, 3, 4}) {
      int b1 = is_bingo_r(i);
      int b2 = is_bingo_c(i);
      b = std::min(b, std::min(b1, b2));
    }

    return b;
  }
};

int day4(line_view file) {
  const char* p1 = file.line;
  const char* p2 = file.line + file.length;
  const char* p = p1;
  bingo b;
  std::vector<board> bs;
  while (p < p2) {
    if (*p == '\n' && *(p + 1) == '\n') {
      if (p1 == file.line) {
        b.parse({p1, p});
      } else {
        bs.emplace_back(line_view{p1, p}, &b);
      }
      p1 = p + 2;
    }
    p++;
  }
  bs.emplace_back(line_view{p1, p}, &b);

  std::sort(bs.begin(), bs.end());
  printf("%d\n", bs[0].sum_unmarked());
  return 0;
}

} // namespace aoc2021
