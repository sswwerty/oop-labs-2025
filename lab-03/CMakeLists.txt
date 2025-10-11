cmake_minimum_required(VERSION 3.10)
project(lab03_oop_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(lab03
    src/main.cpp
    src/Point.cpp
    src/Figure.cpp
    src/Triangle.cpp
    src/Square.cpp
    src/Rectangle.cpp
    src/ArrayFigures.cpp
)

# Tests (GoogleTest) — опционально, включите, если у вас установлен gtest как подмодуль или системный пакет.
enable_testing()
add_subdirectory(test)