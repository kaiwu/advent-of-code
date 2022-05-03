set(TEST_FILES
    catch_main.cpp
    test_common.cpp
    test_2015.cpp
    test_2016.cpp
    test_2017.cpp
    test_2018.cpp
    test_2019.cpp
    test_2020.cpp
    test_2021.cpp
)

add_executable(aoc ${TEST_FILES})
target_include_directories(aoc PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(aoc PRIVATE common solution)
add_test(NAME test_aoc COMMAND aoc
  PROPERTY WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  

