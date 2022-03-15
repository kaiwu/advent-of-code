#include "aoc.h"

namespace aoc2015 {

char* md5sum(char* s) {
  static char md5[64] = {0};
  uint8_t* x = md5String(s);
  memset(md5, 0x0, 64);
  for (auto i = 0; i < 16; i++) {
    sprintf(md5 + i * 2, "%02x", x[i]);
  }
  return md5;
}

int lead_zeros(char* s) {
  char* p = s;
  int total = 0;
  while (*p != '\0') {
    if (*p == '0') {
      total += 1;
      p++;
    }
    else {
      break;
    }
  }
  return total;
}

} // namespace aoc2015
