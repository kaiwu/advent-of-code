#include "common.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

line_view load_file(const char* path) {
  return {nullptr, 0};
}

line_view next_line(const char* file, size_t offset) {
  return {nullptr, 0};
}
