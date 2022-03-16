#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <utility>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

struct line_view {
  const char* line;
  size_t length;

  line_view(const char* s = nullptr) : line(s) { length = s == nullptr ? 0 : strlen(s); }
  line_view(const char* s, size_t l) : line(s), length(l) {}
  line_view(const char* p1, const char* p2) : line(p1), length(p2 - p1 + 1) {}
  friend std::ostream& operator<<(std::ostream& o, const line_view& lv) {
    for (size_t i = 0; i < lv.length; i++) {
      o << lv.line[i];
    }
    return o;
  }

  bool operator==(const line_view& lv) const noexcept {
    const char* p1 = line;
    const char* p2 = lv.line;
    if (length != lv.length) {
      return false;
    }
    while (p1 < p1 + length) {
      if (*p1 != *p2) {
        return false;
      }
      p1++;
      p2++;
    }
    return true;
  }

  const char* contains(const line_view& lv) const noexcept {
    const char* p1 = line;
    const char* p2 = line + length;
    if (length < lv.length) {
      return nullptr;
    }
    while (p1 + lv.length <= p2) {
      if (*p1 == *lv.line) {
        line_view x{p1, lv.length};
        if (x == lv) {
          return p1;
        }
      }
      p1++;
    }
    return nullptr;
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

  const char* contains(const char* s) const noexcept {
    size_t len = strlen(s);
    const char* p = line;
    while (p + len <= line + length) {
      if (*p == *s) {
        line_view x{p, len};
        if (x == s) {
          return p;
        }
      }
      p++;
    }
    return nullptr;
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

template <typename F, typename... Args>
void per_char(line_view line, F&& f, Args&&... args) {
  for (size_t i = 0; i < line.length; i++) {
    if (!f(line.line[i], std::forward<Args>(args)...)) {
      break;
    }
  }
}

struct ascii_count {
  int count[256];

  ascii_count(line_view lv) : count{0} {
    per_char(lv, [this](char c) {
      count[static_cast<int>(c)] += 1;
      return true;
    });
  }

  int operator[](char c) const noexcept { return count[static_cast<int>(c)]; }
  friend std::ostream& operator<<(std::ostream& o, const ascii_count& ac) {
    for (size_t i = 0; i < 256; i++) {
      if (ac.count[i] > 0) {
        o << i << " -> " << ac.count[i] << "\n";
      }
    }
    return o;
  }
};

bool is_repeated(const char* p1, const char* p2);
