#pragma once
#include "common.h"

namespace aoc2015 {

void parse_range(const char* p1, const char* p2, int* total);
void fix_range(const char* p, const char** pe);

int day12(line_view file);
int day12_part2(line_view file);

}
