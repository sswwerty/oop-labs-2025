find_package(GTest REQUIRED)

add_executable(MoneyTests money_test.cpp)
target_link_libraries(MoneyTests MoneyLib GTest::gtest GTest::gtest_main)

add_test(NAME MoneyTests COMMAND MoneyTests)
