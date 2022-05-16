#include "aoc.h"
#include <algorithm>

namespace aoc2021 {

static void get_length(const char** pp, int* d) {
  const char* p = *pp;
  *d = 0;
  while (*p >= 'a' && *p <= 'g') {
    *d += 1;
    p++;
  }
  *pp = p;
}

//   8:
//  aaaa
// b    c
// b    c
//  dddd
// e    f
// e    f
//  gggg
//
//  7, 1 -> a
//  8, 6 -> c
//  8, 9 -> e
//  1, c -> f
//  8, 2 -> b, f
//  8, 3 -> b, e
//  8, 4 -> a, e, g
//  8, 5 -> c, e

struct digit {
  static uint8_t is[];
  uint8_t self = 0;

  // 0..6
  void set(int i) {
    uint8_t m{1};
    self |= m << i;
  }

  // 0..9
  // 0111 0111
  // 0010 0100
  // 0101 1101
  // 0110 1101
  // 0010 1110
  // 0110 1011
  // 0111 1011
  // 0010 0101
  // 0111 1111
  // 0110 1111
  digit(uint8_t i) { self = is[i]; }
  void reset() { self = 0; }
  bool equals(uint8_t i) const noexcept { return self == is[i]; }
  void print() const noexcept {
    const char* letters = "abcdefg";
    for (uint8_t i = 0; i < 7; i++) {
      if (self & (1 << i)) {
        printf("%c", letters[i]);
      }
    }
    printf("\n");
  }
};

uint8_t digit::is[] = {0x77, 0x24, 0x5D, 0x6D, 0x2E, 0x6B, 0x7B, 0x25, 0x7F, 0x6F};

int day8(line_view file) {
  int total{0};
  int ls[14] = {0};
  line_view lvs[14];
  per_line(file, [&ls, &total, &lvs](line_view lv) {
    const char* p = lv.line;
    int index{0};
    while (p < lv.line + lv.length) {
      const char* p1 = p;
      get_length(&p, &ls[index]);
      lvs[index] = line_view{p1, p};
      if (index >= 10) {
        total += int(ls[index] == 2 || ls[index] == 3 || ls[index] == 4 || ls[index] == 7);
      }
      index++;
      p = index == 10 ? p + 3 : p + 1;
    }
    return true;
  });

  // for (int i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
  //   digit(i).print();
  // }
  return total;
}

} // namespace aoc2021
