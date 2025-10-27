cmake_minimum_required(VERSION 3.10)
project(Lab01)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(main src/main.cpp src/box.cpp)
target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Тесты
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(tests tests/test_box.cpp src/box.cpp)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE GTest::GTest GTest::Main Threads::Threads)
