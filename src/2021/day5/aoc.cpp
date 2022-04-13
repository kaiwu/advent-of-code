#include "aoc.h"
#include <algorithm>
#include <vector>

namespace aoc2021 {

static void get_number(const char** pp, int* d) {
  *d = 0;
  const char* p = *pp;
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *pp = p;
}

void fill(std::vector<int>& b1, std::vector<int>& b2, const line& l, int width) {
  int maxx = std::max(l.p1.x, l.p2.x);
  int minx = std::min(l.p1.x, l.p2.x);
  int maxy = std::max(l.p1.y, l.p2.y);
  int miny = std::min(l.p1.y, l.p2.y);

  if (l.p1.x == l.p2.x || l.p1.y == l.p2.y) {
    for (int i = minx; i <= maxx; i++) {
      for (int j = miny; j <= maxy; j++) {
        // printf("[%d, %d]\n", i, j);
        b1[j * width + i] += 1;
        b2[j * width + i] += 1;
        if (b2[j * width + i] > 1) {
          printf("[%d, %d]\n", i, j);
        }
      }
    }
  }

  if (l.p1.x == l.p1.y && l.p2.x == l.p2.y) {
    int j = miny;
    for (int i = minx; i <= maxx; i++) {
      b2[j * width + i] += 1;
      if (b2[j * width + i] > 1) {
        printf("[%d, %d]\n", i, j);
      }
      j++;
    }
  }

  if (l.p1.x == l.p2.y && l.p2.x == l.p1.y) {
    int j = maxy;
    for (int i = minx; i <= maxx; i++) {
      b2[j * width + i] += 1;
      if (b2[j * width + i] > 1) {
        printf("[%d, %d]\n", i, j);
      }
      j--;
    }
  }
}

std::pair<int, int> day5(line_view file) {
  std::vector<line> vs;
  int maxx{INT32_MIN};
  int maxy{INT32_MIN};

  per_line(file, [&vs, &maxx, &maxy](line_view lv) {
    line l;
    int* is[] = {&l.p1.x, &l.p1.y, &l.p2.x, &l.p2.y};
    const char* p = lv.line;
    int i{0};
    while (p < lv.line + lv.length) {
      if (*p >= '0' && *p <= '9') {
        get_number(&p, is[i++]);
      }
      p++;
    }
    maxx = std::max(maxx, std::max(l.p1.x, l.p2.x));
    maxy = std::max(maxy, std::max(l.p1.y, l.p2.y));
    vs.push_back(l);
    return true;
  });

  maxx += 1;
  maxy += 1;

  printf("%d, %d\n", maxx, maxy);
  std::vector<int> board1(maxx * maxy, 0);
  std::vector<int> board2(maxx * maxy, 0);
  for (auto& l : vs) {
    fill(board1, board2, l, maxx);
  }

  int t1{0};
  int t2{0};
  std::for_each(board1.begin(), board1.end(), [&t1](int x) { t1 += int(x >= 2); });
  std::for_each(board2.begin(), board2.end(), [&t2](int x) { t2 += int(x >= 2); });
  return {t1, t2};
}

} // namespace aoc2021
