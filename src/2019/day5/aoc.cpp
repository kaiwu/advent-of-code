#include "aoc.h"

namespace aoc2019 {

static int* input = nullptr;
static int input_sequence = 0;

void get_number(const char** pp, int* d) {
  const char* p = *pp;
  int sign = 1;
  if (*p == '-') {
    sign = -1;
    p++;
  }
  while (*p >= '0' && *p <= '9') {
    *d = *d * 10 + *p - '0';
    p++;
  }
  *d *= sign;
  *pp = p;
}

// 0001
// 0101
// 1001
// 1101
static int mode(int x, int* m1, int* m2) {
  int m{0}, m0{0};
  int* is[] = {&m, &m0, m1, m2};
  int i{0};
  while (x > 0) {
    *is[i++] = x % 10;
    x /= 10;
  }
  return m;
}

static int& get(std::vector<int>& codes, int mode, int i) { return mode == 0 ? codes[codes[i]] : codes[i]; }

static size_t opt1(std::vector<int>& codes, std::vector<int>& outputs, size_t i, int m1, int m2) {
  get(codes, 0, i + 3) = get(codes, m1, i + 1) + get(codes, m2, i + 2);
  return i + 4;
}

static size_t opt2(std::vector<int>& codes, std::vector<int>& outputs, size_t i, int m1, int m2) {
  get(codes, 0, i + 3) = get(codes, m1, i + 1) * get(codes, m2, i + 2);
  return i + 4;
}

static size_t opt3(std::vector<int>& codes, std::vector<int>& outputs, size_t i, int m1, int m2) {
  get(codes, 0, i + 1) = *(input + input_sequence++);
  return i + 2;
}

static size_t opt4(std::vector<int>& codes, std::vector<int>& outputs, size_t i, int m1, int m2) {
  outputs.push_back(get(codes, m1, i + 1));
  return i + 2;
}

static size_t opt5(std::vector<int>& codes, std::vector<int>& outputs, size_t i, int m1, int m2) {
  size_t x = i + 3;
  if (get(codes, m1, i + 1) != 0) {
    x = get(codes, m2, i + 2);
  }
  return x;
}

static size_t opt6(std::vector<int>& codes, std::vector<int>& outputs, size_t i, int m1, int m2) {
  size_t x = i + 3;
  if (get(codes, m1, i + 1) == 0) {
    x = get(codes, m2, i + 2);
  }
  return x;
}

static size_t opt7(std::vector<int>& codes, std::vector<int>& outputs, size_t i, int m1, int m2) {
  get(codes, 0, i + 3) = int(get(codes, m1, i + 1) < get(codes, m2, i + 2));
  return i + 4;
}

static size_t opt8(std::vector<int>& codes, std::vector<int>& outputs, size_t i, int m1, int m2) {
  get(codes, 0, i + 3) = int(get(codes, m1, i + 1) == get(codes, m2, i + 2));
  return i + 4;
}

typedef size_t (*opt_f)(std::vector<int>&, std::vector<int>&, size_t, int, int);
static void run(size_t i, std::vector<int>& codes, std::vector<int>& outputs) {
  // printf("execute %d at %zu\n", codes[i], i);
  static opt_f opts[] = {opt1, opt2, opt3, opt4, opt5, opt6, opt7, opt8};
  if (codes[i] != 99) {
    int m1{0}, m2{0};
    int m = mode(codes[i], &m1, &m2);
    int x = opts[m - 1](codes, outputs, i, m1, m2);
    run(x, codes, outputs);
  }
}

static int run(int i, std::vector<int> codes) {
  input = &i;
  input_sequence = 0;
  std::vector<int> outputs;
  run(0, codes, outputs);
  return outputs[outputs.size() - 1];
}

int int_computer(int i[], std::vector<int> codes) {
  input = i;
  std::vector<int> outputs;
  run(0, codes, outputs);
  return outputs[outputs.size() - 1];
}

std::pair<int, int> day5(line_view file) {
  const char* p = file.line;
  std::vector<int> optcodes;
  while (p < file.line + file.length) {
    if ((*p >= '0' && *p <= '9') || *p == '-') {
      int d{0};
      get_number(&p, &d);
      optcodes.push_back(d);
    }
    p++;
  }
  return {run(1, optcodes), run(5, optcodes)};
}

} // namespace aoc2019
