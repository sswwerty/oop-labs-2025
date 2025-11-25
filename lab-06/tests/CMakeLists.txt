# Подтягиваем GoogleTest
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

set(TEST_SOURCES
    test_factory.cpp
    test_battle.cpp
)

add_executable(balagur_tests ${TEST_SOURCES})
target_link_libraries(balagur_tests
    balagur_lib
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(balagur_tests)
