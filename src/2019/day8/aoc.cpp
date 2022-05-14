#include "aoc.h"
#include <algorithm>

namespace aoc2019 {

struct digits {
  int chars[10] = {0};
};

struct layer {
  char ds[25 * 6] = {0};
};

//static void print(layer * l){
//  for(size_t i = 0; i < ARRAY_SIZE(l->ds); i++) {
//    printf("%s", l->ds[i] > 0 ? "#" : ".");
//    if ((i + 1) % 25 == 0) {
//      printf("\n");
//    }
//  }
//}

static void fold_layers(const char* p1, const char* p2, digits* p, layer* l) {
  int index{0};
  auto reset = [](char x, char y) { return y == 0 || y == 1 ? y : x; };

  while (p1 < p2) {
    p->chars[*p1 - '0'] += 1;
    l->ds[index] = reset(*p1 - '0', l->ds[index]);
    p1++;
    index++;
  }
}

std::pair<int, int> day8(line_view file) {
  digits ds[100];
  int x = 6 * 25;
  layer top;
  memset(&top, 2, sizeof(layer));
  for (int i = 0; i < 100; i++) {
    const char* p1 = file.line + i * x;
    const char* p2 = file.line + (i + 1) * x;
    fold_layers(p1, p2, &ds[i], &top);
  }

  struct ct {
    int zeros = 0;
    int times = 0;
  } cs[100];

  for (int i = 0; i < 100; i++) {
    cs[i].zeros = ds[i].chars[0];
    cs[i].times = ds[i].chars[1] * ds[i].chars[2];
  }

  std::sort(cs, cs + 100, [](ct c1, ct c2) { return c1.zeros < c2.zeros; });
  // print(&top);
  return {cs[0].times, 0};
}
} // namespace aoc2019
