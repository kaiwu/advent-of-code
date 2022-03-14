#include "catch.hpp"
#include "common.h"

TEST_CASE("load file", "[]") {
  line_view file{"\n\n111\n2222\n33333\n", 17};
  const char* lines[] = {"\n", "\n", "111\n", "2222\n", "33333\n"};
  int i = 0;
  per_line(
      file,
      [&i](line_view l, const char* lns[]) {
        REQUIRE(l == lns[i++]);
        return true;
      },
      lines);
}
