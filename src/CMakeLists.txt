set(SOLUTION_FILES
  "2015/day1/aoc.cpp"
)

add_library(solution SHARED ${SOLUTION_FILES})
target_include_directories(solution PRIVATE ${PROJECT_SOURCE_DIR}/src)
