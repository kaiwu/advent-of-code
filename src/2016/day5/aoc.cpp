#include "aoc.h"
#include "md5.h"
#include <string.h>

namespace aoc2016 {

void day5(const char* secret, int len, char pass1[], char pass2[]) {
  char buf[128] = {0};
  int l = strlen(secret);
  memcpy(buf, secret, len);
  int64_t i = 0;
  int x1 = len;
  int x2 = 0;
  while (i < INT64_MAX && x2 < 8) {
    sprintf(buf + l, "%lld", i);
    char* hash = md5sum(buf);
    if (lead_zeros(hash) >= 5) {
      printf("%lld %s\n", i, hash);
      if (x1 > 0) {
        pass1[len - x1] = hash[5];
        x1--;
      }
      if (hash[5] >= '0' && hash[5] <= '7' && pass2[hash[5] - '0'] == '\0') {
        pass2[hash[5] - '0'] = hash[6];
        x2 += 1;
      }
    }
    i++;
  }
}

} // namespace aoc2016
