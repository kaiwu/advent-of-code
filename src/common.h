#pragma once

#include <stdlib.h>
#include <utility>

struct line_view {
  const char* line;
  size_t length;
};

line_view load_file(const char*);
line_view next_line(line_view, size_t*);

template <typename F, typename... Args>
void per_line(line_view file, F&& f, Args&&... args) {
  size_t offset = 0;
  line_view lv;
  do {
    lv = next_line(file, &offset);
    if (!f(lv, std::forward<Args>(args)...)) {
      break;
    }
  } while (offset < file.length);
}
