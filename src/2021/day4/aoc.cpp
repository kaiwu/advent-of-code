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
  bnum at;

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
    //print();
  }

  void print() const noexcept {
    int i{0};
    for (auto& b : is) {
      printf("{%02d,%02d}", b.v, b.i);
      if (++i % 5 == 0) {
        printf("\n");
      } else {
        printf(" ");
      }
    }
    printf("-> %d %d\n", at.v, at.i);
  }

  int sum_unmarked(int x) {
    int s{0};
    for (auto& n : is) {
      if (n.i > x) {
        // printf("%d ", n.v);
        s += n.v;
      }
    }
    return s;
  }

  bool operator<(const board& b) const noexcept { return at.i < b.at.i; }
  bnum bingo_at() const noexcept {
    auto is_bingo_r = [this](int y) -> bnum {
      int m{INT32_MIN};
      int v{0};
      for (int x : {0, 1, 2, 3, 4}) {
        auto p = is[y * 5 + x].i;
        if (p == INT32_MAX) {
          return {INT32_MAX, v};
        } else {
          if (p > m) {
            m = p;
            v = is[y * 5 + x].v;
          }
        }
      }
      // printf("row %d is {%d, %d}\n", y, v, m);
      return {m, v};
    };

    auto is_bingo_c = [this](int x) -> bnum {
      int m{INT32_MIN};
      int v{0};
      for (int y : {0, 1, 2, 3, 4}) {
        auto p = is[y * 5 + x].i;
        if (p == INT32_MAX) {
          return {INT32_MAX, v};
        } else {
          if (p > m) {
            m = p;
            v = is[y * 5 + x].v;
          }
        }
      }
      // printf("col %d is {%d, %d}\n", x, v, m);
      return {m, v};
    };

    bnum b{INT32_MAX, 0};
    for (int i : {0, 1, 2, 3, 4}) {
      bnum b1 = is_bingo_r(i);
      bnum b2 = is_bingo_c(i);

      bnum bx{0, 0};
      bx.i = b1.i < b2.i ? b1.i : b2.i;
      bx.v = b1.i < b2.i ? b1.v : b2.v;

      if (bx.i < b.i) {
        b = bx;
      }
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
  // for (auto& b : bs) {
  //   printf("%d, %d\n", b.at.i, b.sum_unmarked(b.at.i) * b.at.v);
  // }
  return bs[0].sum_unmarked(bs[0].at.i) * bs[0].at.v;
}

} // namespace aoc2021
