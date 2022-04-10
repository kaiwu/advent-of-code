#include "aoc.h"
#include <math.h>

namespace aoc2018 {

void deduct(char** pp1, char** pp2, char* b, char* e) {
  char* p1 = *pp1;
  char* p2 = *pp2;
  while (p1 >= b && p2 < e) {
    bool stop = true;
    if (std::abs(*p1 - *p2) == 32) {
      *p1 = ' ';
      *p2 = ' ';
      p1--;
      p2++;
      stop = false;
    }
    if (*p1 == ' ') {
      p1--;
      stop = false;
    }
    if (*p2 == ' ') {
      p2++;
      stop = false;
    }
    if (stop) {
      break;
    }
  }
  *pp1 = p1;
  *pp2 = p2;
}

int count(line_view lv) {
  int total{0};
  auto is_az = [](char c) { return c >= 'a' && c <= 'z'; };
  auto is_AZ = [](char c) { return c >= 'A' && c <= 'Z'; };
  per_char(lv, [&total, &is_az, &is_AZ](char c) {
    if (is_az(c) || is_AZ(c)) {
      total += 1;
    }
    return true;
  });
  return total;
}

void deduct(char* p1, char* p2) {
  char* p = p1;
  while (p < p2) {
    if (std::abs(*p - *(p + 1)) == 32) {
      char* pa = p;
      char* pb = p + 1;
      deduct(&pa, &pb, p1, p2);
      p = pb;
    } else {
      p++;
    }
  }
}

void print(char* p1, char* p2) {
  while (p1 < p2) {
    if (*p1 != ' ') {
      std::cout << *p1;
    }
    p1++;
  }
  printf("\n");
}

int day5(line_view file) {
  char* p1 = (char*)malloc(file.length);
  memcpy(p1, file.line, file.length);
  char* p2 = p1 + file.length;
  deduct(p1, p2);
  // print(p1, p2);
  return count({p1, p2});
}

} // namespace aoc2018
