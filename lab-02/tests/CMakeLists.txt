cmake_minimum_required(VERSION 3.16)
project(MoneyTests)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_money test_money.cpp)

target_include_directories(test_money PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(test_money PRIVATE
    money_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_money)