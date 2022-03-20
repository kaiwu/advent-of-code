#pragma once
#include "common.h"

namespace aoc2015 {
struct sue {
  int children = -1;
  int cats = -1;
  int samoyeds = -1;
  int pomeranians = -1;
  int akitas = -1;
  int vizslas = -1;
  int goldfish = -1;
  int trees = -1;
  int cars = -1;
  int perfumes = -1;

  sue() {}
  sue(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9) {
    children = i0;
    cats = i1;
    samoyeds = i2;
    pomeranians = i3;
    akitas = i4;
    vizslas = i5;
    goldfish = i6;
    trees = i7;
    cars = i8;
    perfumes = i9;
  }

  bool like(const sue& x) const noexcept {
    const int* is0[] = {
        &children, &cats, &samoyeds, &pomeranians, &akitas, &vizslas, &goldfish, &trees, &cars, &perfumes,
    };
    const int* is1[] = {
        &x.children, &x.cats,     &x.samoyeds, &x.pomeranians, &x.akitas,
        &x.vizslas,  &x.goldfish, &x.trees,    &x.cars,        &x.perfumes,
    };

    for (size_t i = 0; i < ARRAY_SIZE(is0); i++) {
      if (*is0[i] != -1 && *is0[i] != *is1[i]) {
        return false;
      }
    }
    return true;
  }

  bool like_range(const sue& x) const noexcept {
    const int* is0[] = {
        &children, &cats, &samoyeds, &pomeranians, &akitas, &vizslas, &goldfish, &trees, &cars, &perfumes,
    };
    const int* is1[] = {
        &x.children, &x.cats,     &x.samoyeds, &x.pomeranians, &x.akitas,
        &x.vizslas,  &x.goldfish, &x.trees,    &x.cars,        &x.perfumes,
    };
    auto p1 = [](const int* i0, const int* i1) -> bool { return *i0 == *i1; };
    auto p2 = [](const int* i0, const int* i1) -> bool { return *i0 > *i1; };
    auto p3 = [](const int* i0, const int* i1) -> bool { return *i0 < *i1; };

    std::function<bool(const int*, const int*)> f[] = {
        p1, p2, p1, p3, p1, p1, p3, p2, p1, p1,
    };

    for (size_t i = 0; i < ARRAY_SIZE(is0); i++) {
      if (*is0[i] != -1 && !(f[i])(is0[i], is1[i])) {
        return false;
      }
    }
    return true;
  }
};

bool like(const sue& s1, const sue& s2);
bool like_range(const sue& s1, const sue& s2);

struct aunts {
  sue as[500];

  int get_number(const char* p) {
    int d{0};
    while ((*p) >= '0' && (*p) <= '9') {
      d = d * 10 + *p - '0';
      p++;
    }
    return d;
  }

  typedef bool(*likef)(const sue&, const sue&);
  int filter(sue s, likef f) {
    for (size_t i = 0; i < ARRAY_SIZE(as); i++) {
      if (f(as[i],s)) {
        return i + 1;
      }
    }
    return -1;
  }

  void parse(line_view lv) {
    static const char* keys[] = {
        "children", "cats", "samoyeds", "pomeranians", "akitas", "vizslas", "goldfish", "trees", "cars", "perfumes",
    };
    sue x;
    int i = get_number(lv.line + 4);
    int* is[] = {
        &x.children, &x.cats,     &x.samoyeds, &x.pomeranians, &x.akitas,
        &x.vizslas,  &x.goldfish, &x.trees,    &x.cars,        &x.perfumes,
    };
    for (size_t k = 0; k < ARRAY_SIZE(keys); k++) {
      const char* p = lv.contains(keys[k]);
      if (p != nullptr) {
        *is[k] = get_number(p + strlen(keys[k]) + 2);
        // printf("%d %s %d\n", i, keys[k], *is[k]);
      }
    }

    as[i - 1] = x;
  }
};

std::pair<int,int> day16(line_view);

} // namespace aoc2015
