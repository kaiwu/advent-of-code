#pragma once

#include "common.h"
#include <vector>

namespace aoc2019 {

void set_computer(int* i);
int run_computer(std::vector<int> codes);

typedef bool (*interrupt_f)(size_t, std::vector<int>&, void *);
void run_computer(size_t i, std::vector<int>& codes, std::vector<int>&, interrupt_f, void *);

std::pair<int, int> day5(line_view);
}
