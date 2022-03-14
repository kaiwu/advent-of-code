#pragma once

#include <stdlib.h>

struct line_view {
  char* line;
  size_t length;
};

line_view load_file(const char*);
line_view next_line(const char*, size_t);
