cmake_minimum_required(VERSION 3.14)

# Подключаем модуль FetchContent
include(FetchContent)

# Загружаем GoogleTest с GitHub
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Чтобы не было конфликтов с системой
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Добавляем тестовый исполняемый файл
add_executable(runTests
    test_area.cpp
    ../src/Point.cpp
    ../src/Figure.cpp
    ../src/Triangle.cpp
    ../src/Square.cpp
    ../src/Rectangle.cpp
    ../src/ArrayFigures.cpp
)

# Пути к заголовкам
target_include_directories(runTests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Подключаем GTest
target_link_libraries(runTests
    GTest::gtest
    GTest::gtest_main
)

# Добавляем команду для запуска тестов
enable_testing()
add_test(NAME runTests COMMAND runTests)