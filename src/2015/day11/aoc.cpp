#include "aoc.h"

namespace aoc2015 {

bool is_valid_rule1(int* is) {
  auto is_valid = [](int* p) -> bool { return (*p + 1 == *(p + 1)) && (*p + 2 == *(p + 2)); };
  for (int i = 0; i < 6; i++) {
    if (is_valid(is + i)) {
      return true;
    }
  }
  return false;
}

bool is_valid_rule3(int* is) {
  int* p1 = nullptr;
  int* p2 = nullptr;
  int* p3 = is + 7;
  while (is < p3) {
    if (*is == *(is + 1)) {
      if (p1 == nullptr) {
        p1 = is;
      } else {
        p2 = is;
      }
      is += 2;
    } else {
      is += 1;
    }
  }
  return p1 != nullptr && p2 != nullptr && *p1 != *p2;
}

// int* 0..25
void next(int* is, int* invalids, int n) {
  // increatment
  for (int x = 7; x >= 0; x--) {
    if (is[x] == 'z' - 'a') {
      is[x] = 0;
    } else {
      is[x] += 1;
      break;
    }
  }

  auto is_invalid = [invalids, n](int x) -> bool {
    for (int j = 0; j < n; j++) {
      if (x == invalids[j]) {
        return true;
      }
    }
    return false;
  };

  for (int x = 0; x < 8; x++) {
    if (is_invalid(is[x])) { // is[x] = 'i' 'j' 'o'
      is[x] = is[x] == 25 ? 0 : is[x] + 1;
      for (int k = x + 1; k < 8; k++) {
        is[k] = 0;
      }
      break;
    }
  }
}

char* day11(const char* pass) {
  int invalids[] = {'i' - 'a', 'o' - 'a', 'l' - 'a'};
  int indexes[8] = {0};
  for (int i = 0; i < 8; i++) {
    indexes[i] = pass[i] - 'a';
  }

  bool b1 = false;
  bool b3 = false;

  do {
    next(indexes, invalids, ARRAY_SIZE(invalids));
    b1 = is_valid_rule1(indexes);
    b3 = is_valid_rule3(indexes);
  } while (!b1 || !b3);

  char* password = (char*)malloc(9);
  for (int i = 0; i < 8; i++) {
    password[i] = 'a' + indexes[i];
  }
  password[8] = '\0';

  return password;
}

} // namespace aoc2015
