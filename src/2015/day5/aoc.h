#pragma once
#include "common.h"

namespace aoc2015 {

int count_vowels(line_view, const char*);
bool is_nice(line_view, int);
bool is_nice(line_view, const char*[], size_t);
bool is_interleaved(line_view);
bool has_no_overlap_pair(line_view);

std::pair<int,int> day5(line_view);

}
