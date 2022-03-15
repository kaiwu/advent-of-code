cmake_minimum_required(VERSION 3.8)
project(advent-of-code LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -pedantic -Wno-unused-parameter")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS Off)

set(COMMON_FILES
    "src/common.cpp"
)

add_library(common SHARED ${COMMON_FILES})
add_subdirectory(src)

enable_testing()
add_subdirectory(test)

