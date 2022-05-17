#include "aoc.h"
#include <algorithm>
#include <vector>

namespace aoc2021 {

static void get_length(const char** pp) {
  const char* p = *pp;
  while (*p >= 'a' && *p <= 'g') {
    p++;
  }
  *pp = p;
}

// abcdefg
static char diff(line_view l1, line_view l2) {
  char d[7] = {0};
  auto add = [&d](line_view l) {
    const char* p = l.line;
    while (p < l.line + l.length) {
      d[*p - 'a'] += 1;
      p++;
    }
  };
  add(l1);
  add(l2);
  for (int i = 0; i < 7; i++) {
    if (d[i] == 1) {
      return 'a' + i;
    }
  }
  return 0;
}

struct digit {
  static uint8_t is[];
  uint8_t self = 0;

  digit() { self = 0; }
  digit(uint8_t i) { self = is[i]; }

  void reset() { self = 0; }
  void add(uint8_t x) { self |= x; }
  void print() const noexcept {
    const char* letters = "abcdefg";
    for (uint8_t i = 0; i < 7; i++) {
      if (self & (1 << i)) {
        printf("%c", letters[i]);
      }
    }
    printf("\n");
  }

  uint8_t value() const noexcept {
    for (uint8_t i = 0; i < 10; i++) {
      if (is[i] == self) {
        return i;
      }
    }
    return UINT8_MAX;
  }

  static uint8_t _or(digit d1, digit d2) noexcept { return d1.self | d2.self; }
  static uint8_t _and(digit d1, digit d2) noexcept { return d1.self & d2.self; }
  static uint8_t _xor(digit d1, digit d2) noexcept { return d1.self ^ d2.self; }

  //   8:
  //  aaaa
  // b    c
  // b    c
  //  dddd
  // e    f
  // e    f
  //  gggg

  static uint8_t get_a() { return _xor(digit(7), digit(1)); }
  static uint8_t get_e() { return _xor(digit(8), digit(9)); }
  static uint8_t get_d() { return _xor(digit(8), digit(0)); }
  static uint8_t get_c() { return _xor(digit(8), digit(6)); }
  static uint8_t get_f() { return digit(1).self ^ get_c(); }
  static uint8_t get_b() { return _xor(digit(8), digit(2)) ^ get_f(); }
  static uint8_t get_g() { return 0x40; }

  static void bprint(uint8_t x) noexcept {
    for (uint8_t i = 8; i > 0; i--) {
      printf("%d", (x & (1 << (i - 1))) > 0 ? 1 : 0);
    }
    printf("\n");
  }

  static void test() {
    bprint(get_a());
    bprint(get_b());
    bprint(get_c());
    bprint(get_d());
    bprint(get_e());
    bprint(get_f());
    bprint(get_g());
  }
};

uint8_t digit::is[] = {0x77, 0x24, 0x5D, 0x6D, 0x2E, 0x6B, 0x7B, 0x25, 0x7F, 0x6F};

struct digitx {
  line_view lv;

  uint8_t get(uint8_t* digits) {
    switch (lv.length) {
    case 2:
      return 1;
    case 3:
      return 7;
    case 4:
      return 4;
    case 7:
      return 8;
    default:
      digit d;
      const char* p = lv.line;
      while (p < lv.line + lv.length) {
        d.add(digits[*p - 'a']);
        p++;
      }
      return d.value();
    }
  }
};

int toint(digitx* d, uint8_t* digits) {
  int x{0};
  digitx* e = d + 4;
  while (d < e) {
    x = x * 10 + d->get(digits);
    d += 1;
  }
  return x;
}

void get_digits(digitx* ds, uint8_t* digits) {
  auto find = [](digitx* d, size_t l) -> std::vector<line_view> {
    std::vector<line_view> vs;
    for (int i = 0; i < 10; i++) {
      if (d[i].lv.length == l) {
        vs.push_back(d[i].lv);
      }
    }
    return vs;
  };

  auto fc = [](line_view lv, char c) -> bool {
    const char* p = lv.line;
    while (p < lv.line + lv.length) {
      if (*p == c) {
        return true;
      }
      p++;
    }
    return false;
  };

  //   8:
  //  aaaa
  // b    c
  // b    c
  //  dddd
  // e    f
  // e    f
  //  gggg

  auto lv1 = find(ds, 2)[0];
  auto lv4 = find(ds, 4)[0];
  auto lv7 = find(ds, 3)[0];
  auto lv8 = find(ds, 7)[0];
  auto lv069 = find(ds, 6);

  char c7[7] = {0};
  char a = diff(lv1, lv7);
  digits[a - 'a'] = digit::get_a();
  c7[0] = a;

  char c4[4] = {0};
  for (size_t i = 0; i < lv069.size(); i++) {
    char c = diff(lv8, lv069[i]);
    if (!fc(lv4, c)) {
      digits[c - 'a'] = digit::get_e();
      c7[1] = c;
    } else {
      if (!fc(lv1, c)) {
        digits[c - 'a'] = digit::get_d();
        c4[0] = c;
        c7[2] = c;
      } else {
        digits[c - 'a'] = digit::get_c();
        c4[1] = c;
        c7[3] = c;
        char f = *lv1.line == c ? *(lv1.line + 1) : *lv1.line;
        digits[f - 'a'] = digit::get_f();
        c4[2] = f;
        c7[4] = f;
      }
    }
  }

  char b = diff(lv4, line_view{c4, 4});
  digits[b - 'a'] = digit::get_b();
  c7[5] = b;

  char g = diff(lv8, line_view{c7, 7});
  digits[g - 'a'] = digit::get_g();

  // for (int i = 0; i < 14; i++) {
  //   printf("%d ", ds[i].get(digits));
  // }
  // printf("\n");
}

std::pair<int, int> day8(line_view file) {
  int t0{0};
  int t1{0};

  auto is1478 = [](line_view lv) -> bool {
    auto b1 = lv.length == 2;
    auto b2 = lv.length == 3;
    auto b3 = lv.length == 4;
    auto b4 = lv.length == 7;
    return b1 || b2 || b3 || b4;
  };

  per_line(file, [&t0, &t1, &is1478](line_view lv) {
    digitx ds[14];
    const char* p = lv.line;
    int index{0};
    while (p < lv.line + lv.length) {
      const char* p1 = p;
      get_length(&p);
      ds[index].lv = line_view{p1, p};
      if (index >= 10) {
        t0 += int(is1478(ds[index].lv));
      }
      index++;
      p = index == 10 ? p + 3 : p + 1;
    }

    uint8_t digits[7] = {0};
    get_digits(ds, digits);
    t1 += toint(ds + 10, digits);
    return true;
  });

  return {t0, t1};
}

} // namespace aoc2021
