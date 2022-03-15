#include "common.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

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
  close(fd);
  return lv;
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
