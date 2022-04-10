#include "aoc.h"

namespace aoc2015 {

int day4(const char* secret, int target) {
  char buf[128] = {0};
  int len = strlen(secret);
  memcpy(buf, secret, len);
  int i = 1;
  while (i < INT32_MAX) {
    sprintf(buf+len, "%d", i);
    if (lead_zeros(md5sum(buf)) >= target) {
      break;
    }
    i++;
  }
  return i;
}

} // namespace aoc2015
