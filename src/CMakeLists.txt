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
  "2015/day11/aoc.cpp"
  "2015/day12/aoc.cpp"
  "2015/day13/aoc.cpp"
  "2015/day14/aoc.cpp"
  "2015/day15/aoc.cpp"
  "2015/day16/aoc.cpp"
  "2015/day17/aoc.cpp"
  "2015/day18/aoc.cpp"
  "2015/day19/aoc.cpp"
  "2015/day20/aoc.cpp"
  "2015/day21/aoc.cpp"
  "2015/day22/aoc.cpp"

  "2016/day1/aoc.cpp"
  "2016/day2/aoc.cpp"

  "2017/day1/aoc.cpp"
  "2017/day2/aoc.cpp"

  "2018/day1/aoc.cpp"
  "2018/day2/aoc.cpp"

  "2019/day1/aoc.cpp"
  "2019/day2/aoc.cpp"

  "2020/day1/aoc.cpp"
  "2020/day2/aoc.cpp"

  "2021/day1/aoc.cpp"
  "2021/day2/aoc.cpp"
)

add_library(solution SHARED ${SOLUTION_FILES})
target_include_directories(solution PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(solution PRIVATE common)
