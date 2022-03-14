#include "common.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

line_view load_file(const char* path) {
  int fd;
  struct stat fs;
  fd = open(path, O_RDONLY);
  if (fd == -1)
    return {nullptr, 0};
  if (fstat(fd, &fs) == -1)
    return {nullptr, 0};

  line_view lv;
  lv.length = fs.st_size;
  lv.line = static_cast<const char*>(mmap(NULL, lv.length, PROT_READ, MAP_PRIVATE, fd, 0));
  return lv;
}

line_view next_line(line_view file) {
  return {nullptr, 0};
}
