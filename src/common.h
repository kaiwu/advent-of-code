#pragma once

#include <stdlib.h>

struct line_view {
  const char* line;
  size_t length;
};

line_view load_file(const char*);
line_view next_line(line_view);
