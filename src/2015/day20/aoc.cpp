#include "aoc.h"
#include <algorithm>
#include <set>
#include <vector>

namespace aoc2015 {

std::pair<int, int> by2(int x, int factor) {
  int a = 0;
  while (true) {
    int total = 0;
    for (int i = 0; i <= a; i++) {
      total += 1 << i;
    }
    // printf("%d -> %d\n", a, total * 10);
    if (total * factor > x) {
      return {1 << (a - 1), 1 << a};
    }
    a++;
  }
}

std::vector<int> primefactor(int x) {
  std::vector<int> v;
  while (x % 2 == 0) {
    v.push_back(2);
    x /= 2;
  }
  for (int i = 3; i * i <= x; i += 2) {
    while (x % i == 0) {
      v.push_back(i);
      x /= i;
    }
  }
  if (x > 2) {
    v.push_back(x);
  }

  return v;
}

// backtrace
void combo(size_t m, size_t x, std::vector<int>& is, std::set<int>& rs, const std::vector<int>& ps) {
  if (is.size() >= m) {
    int x = 1;
    std::for_each(is.begin(), is.end(), [&x, &ps](int i) { x *= ps[i]; });
    rs.insert(x);
  } else {
    for (size_t i = x; i < ps.size(); i++) {
      is.push_back(i);
      combo(m, i + 1, is, rs, ps);
      is.pop_back();
    }
  }
}

int combo(int i, int factor) {
  std::vector<int> ps = primefactor(i);
  std::vector<int> is;
  std::set<int> rs;
  rs.insert(1);
  rs.insert(i);
  for (size_t i = 1; i < ps.size(); i++) {
    combo(i, 0, is, rs, ps);
  }

  int total{0};
  std::for_each(rs.begin(), rs.end(), [&total, factor](int x) {
    // int d = i / x;
    // if (d <= 50) {
    total += x * factor;
    // }
  });
  return total;
}

int left_bound(std::pair<int, int> p, int target, int factor) {
  // int left = p.first;
  // int right = p.second;
  // while (left <= right) {
  //   int mid = left + (right - left) / 2;
  //   int x = combo(mid);
  //   if (x > target) {
  //     right = mid - 1;
  //   } else if (x < target) {
  //     left = mid + 1;
  //   } else if (x == target) {
  //     right = mid - 1;
  //   }
  // }

  for (int i = p.first / 2; i < p.second; i++) {
    int x = combo(i, factor);
    // printf("%d %d\n", i, x);
    if (x >= target) {
      return i;
    }
  }
  return p.second;
}

std::pair<int, int> day20(int x, int factor) {
  auto p = by2(x, factor);
  int m = left_bound(p, x, factor);
  return {m, 884520};
}

} // namespace aoc2015
