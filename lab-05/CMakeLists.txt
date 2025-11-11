cmake_minimum_required(VERSION 3.14)
project(lab05_pmr_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lab05 INTERFACE)
target_include_directories(lab05 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(main_app src/main.cpp)
target_link_libraries(main_app PRIVATE lab05)

# тест
enable_testing()
add_executable(test_basic tests/test_basic.cpp)
target_link_libraries(test_basic PRIVATE lab05)
add_test(NAME BasicTest COMMAND test_basic)
