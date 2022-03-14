#pragma once

#include <iostream>
#include <stdlib.h>
#include <utility>

struct line_view {
  const char* line;
  size_t length;

  friend std::ostream& operator<<(std::ostream& o, const line_view& lv) {
    for (size_t i = 0; i < lv.length; i++) {
      o << lv.line[i];
    }
    return o;
  }

  bool operator==(const char* l) const noexcept {
    size_t i = 0;
    while (i < this->length) {
      if (l[i] != this->line[i]) {
        return false;
      }
      i++;
    }
    return l[i] == '\0';
  }
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
