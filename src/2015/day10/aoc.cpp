#include "aoc.h"
#include <stdlib.h>
#include <string>

namespace aoc2015 {

int len(int i) {
  int x{0};
  while (i > 0) {
    i = i / 10;
    x++;
  }
  return x;
}

void itoa(int i, char* s) {
  if (i < 10) {
    *s = '0' + i;
  } else {
    int x = i % 10;
    *s = '0' + x;
    itoa(i / 10, s--);
  }
}

void record(const char* p1, const char* p2, std::string& x) {
  char c = *p1;
  int d = p2 - p1;
  int l = len(d);
  char* s = (char*)malloc(l + 1);
  s[l] = '\0';
  itoa(d, s + l - 1);
  x.append(s);
  x.append(1, c);
  free(s);
}

std::string look_and_say(const char* s) {
  std::string x;
  const char* p1 = s;
  const char* p2 = s;
  while (*p2 != '\0') {
    if (*p2 != *p1) {
      record(p1, p2, x);
      p1 = p2;
    }
    p2++;
  }
  record(p1, p2, x);
  return x;
}

size_t day10(const char* s, int repeat) {
  std::string x(s);
  for (int i = 0; i < repeat; i++) {
    // printf("%s\n", x.c_str());
    x = look_and_say(x.c_str());
  }
  return x.size();
}

} // namespace aoc2015
