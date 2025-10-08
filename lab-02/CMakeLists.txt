cmake_minimum_required(VERSION 3.14)
project(MoneyClass)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная библиотека
add_library(MoneyLib Money.cpp)
target_include_directories(MoneyLib PUBLIC .)

# Пример программы
add_executable(main_example main.cpp)
target_link_libraries(main_example MoneyLib)

# Тесты
enable_testing()
add_subdirectory(tests)