#pragma once
#include "common.h"
#include <map>
#include <vector>

namespace aoc2016 {

struct keybad {
  enum move {
    up,
    right,
    down,
    left,
  };

  std::map<char, std::vector<char>> digit_keys = {
      {'1', {1, 2, 4, 1}}, {'2', {2, 3, 5, 1}}, {'3', {3, 3, 6, 2}}, {'4', {1, 5, 7, 4}}, {'5', {2, 6, 8, 4}},
      {'6', {3, 6, 9, 5}}, {'7', {4, 8, 7, 7}}, {'8', {5, 9, 8, 7}}, {'9', {6, 9, 9, 8}},
  };

  std::map<char, std::vector<char>> diamond_keys = {
      {'1', {'1', '1', '3', '1'}}, {'2', {'2', '3', '6', '2'}}, {'3', {'1', '4', '7', '2'}},
      {'4', {'4', '4', '8', '3'}}, {'5', {'5', '6', '5', '5'}}, {'6', {'2', '7', 'A', '5'}},
      {'7', {'3', '8', 'B', '6'}}, {'8', {'4', '9', 'C', '7'}}, {'9', {'9', '9', '9', '8'}},
      {'A', {'6', 'B', 'A', 'A'}}, {'B', {'7', 'C', 'D', 'A'}}, {'C', {'8', 'C', 'C', 'B'}},
      {'D', {'B', 'D', 'D', 'D'}},
  };

  // clang-format off
  int az[26] = {
      INT_MAX, INT_MAX, INT_MAX, 2,
      INT_MAX, INT_MAX, INT_MAX,
      INT_MAX, INT_MAX,
      INT_MAX, INT_MAX, 3,
      INT_MAX, INT_MAX, INT_MAX,
      INT_MAX, INT_MAX, 1,
      INT_MAX, INT_MAX, 0,
      INT_MAX, INT_MAX, INT_MAX,
      INT_MAX, INT_MAX,
  };
  // clang-format on

  char touch(char i, const char* p, std::map<char, std::vector<char>>& keys) {
    while (*p >= 'A' && *p <= 'Z') {
      i = keys[char(i + '0')][az[*p - 'A']];
      p++;
    }
    return i;
  }

  void touch(size_t i, char codes[], const char* p, std::map<char, std::vector<char>>& keys) {
    char x = i == 0 ? '5' : codes[i - 1];
    while (*p >= 'A' && *p <= 'Z') {
      x = keys[x][az[*p - 'A']];
      p++;
    }
    codes[i] = x;
  }
};

int day2(line_view, char[]);

} // namespace aoc2016
