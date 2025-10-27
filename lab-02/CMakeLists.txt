cmake_minimum_required(VERSION 3.14)
project(Lab04_Money LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(money_lib
    src/Money.cpp
    src/Money.h
)

add_executable(main_program
    src/main.cpp
)
target_link_libraries(main_program PRIVATE money_lib)

enable_testing()
add_subdirectory(tests)

set_target_properties(main_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)