set(SOLUTION_FILES
  "2015/day1/aoc.cpp"
  "2015/day2/aoc.cpp"
  "2015/day3/aoc.cpp"
  "2015/day4/md5.cpp"
  "2015/day4/aoc.cpp"
  "2015/day5/aoc.cpp"
  "2015/day6/aoc.cpp"
  "2015/day7/aoc.cpp"
  "2015/day8/aoc.cpp"
  "2015/day9/aoc.cpp"
  "2015/day10/aoc.cpp"
)

add_library(solution SHARED ${SOLUTION_FILES})
target_include_directories(solution PRIVATE ${PROJECT_SOURCE_DIR}/src)
