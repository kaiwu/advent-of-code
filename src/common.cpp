#include "common.h"
#include <fcntl.h>
#include <unistd.h>

static size_t file_size(FILE* fd, size_t s) {
  char buf[1024];
  size_t x = fread(buf, sizeof(char), 1024, fd);
  if (x < 1024) {
    return x + s;
  }
  else {
    return file_size(fd, x + s);
  }
}


line_view load_file(const char* path) {
  FILE* fd = fopen(path, "r");
  if (fd == nullptr) {
    return {nullptr, size_t(0)};
  }
  size_t size = file_size(fd, 0);
  fseek(fd, 0, SEEK_SET);
  char* ptr = (char *) malloc(size);
  return {ptr, size};
}

line_view next_line(line_view file, size_t* offset) {
  const char* p1 = file.line + *offset;
  const char* p2 = p1;
  const char* end = file.line + file.length;
  while (p2 < end && *p2 != '\n') {
    p2++;
  }
  *offset = p2 - file.line + 1;
  return {p1, static_cast<size_t>(p2 - p1 + 1)};
}

bool is_repeated(const char* p1, const char* p2) {
  char c = *p1;
  while (p1 != p2) {
    if (*p1 != c) {
      return false;
    }
    p1++;
  }
  return true;
}
