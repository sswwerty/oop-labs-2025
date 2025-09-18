cmake_minimum_required(VERSION 3.10)
project(Lab01)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

# Основная программа
add_executable(main src/main.cpp src/box.cpp)

# Где искать заголовки
target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Тесты
add_executable(tests tests/test_box.cpp src/box.cpp)

# Подключаем GTest
target_link_libraries(tests PRIVATE GTest::GTest GTest::Main)

# Подключить include/
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)