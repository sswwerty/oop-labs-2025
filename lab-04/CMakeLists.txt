cmake_minimum_required(VERSION 3.16)
project(lab04_oop_meta LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(lab04
    src/main.cpp
)

# Tests
add_executable(tests
    tests/test_shapes.cpp
)

if (APPLE)
    target_compile_options(lab04 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
else()
    target_compile_options(lab04 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
endif()
