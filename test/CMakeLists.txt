set(TEST_FILES
    catch_main.cpp
    test_2015.cpp
)

add_executable(aoc ${TEST_FILES})
target_include_directories(aoc PRIVATE ${PROJECT_SOURCE_DIR}/include)
add_test(NAME test_aoc COMMAND aoc)
  

