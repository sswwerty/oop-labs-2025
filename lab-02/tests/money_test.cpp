#include <gtest/gtest.h>
#include "../Money.h"

TEST(MoneyTest, DefaultConstructor) {
    Money m;
    EXPECT_EQ(m.toString(), "0.00");
}

TEST(MoneyTest, StringConstructorNormal) {
    Money m("123.45");
    EXPECT_EQ(m.toString(), "123.45");
}

TEST(MoneyTest, StringWithoutKopecks) {
    Money m("100");
    EXPECT_EQ(m.toString(), "100.00");
}

TEST(MoneyTest, OneKopeckDigit) {
    Money m("50.5");
    EXPECT_EQ(m.toString(), "50.50");
}

TEST(MoneyTest, Addition) {
    Money m1("10.50");
    Money m2("20.60");
    Money result = m1 + m2;
    EXPECT_EQ(result.toString(), "31.10");
}

TEST(MoneyTest, Subtraction) {
    Money m1("100.00");
    Money m2("25.75");
    Money result = m1 - m2;
    EXPECT_EQ(result.toString(), "74.25");
}

TEST(MoneyTest, SubtractToZero) {
    Money m1("10.00");
    Money m2("10.00");
    Money result = m1 - m2;
    EXPECT_EQ(result.toString(), "0.00");
}

TEST(MoneyTest, Comparison) {
    Money m1("100.00");
    Money m2("99.99");
    EXPECT_TRUE(m1 > m2);
    EXPECT_TRUE(m2 < m1);
    EXPECT_FALSE(m1 == m2);
}

TEST(MoneyTest, EqualValues) {
    Money m1("50.00");
    Money m2("50.00");
    EXPECT_TRUE(m1 == m2);
}

TEST(MoneyTest, InvalidInputTooManyKopecks) {
    EXPECT_THROW(Money("10.123"), Money::InvalidMoneyException);
}

TEST(MoneyTest, InvalidInputLetters) {
    EXPECT_THROW(Money("abc"), Money::InvalidMoneyException);
}

TEST(MoneyTest, NegativeSubtraction) {
    Money m1("10.00");
    Money m2("20.00");
    EXPECT_THROW(m1 - m2, Money::NegativeResultException);
}

TEST(MoneyTest, CopyConstructor) {
    Money m1("123.45");
    Money m2 = m1;
    EXPECT_EQ(m2.toString(), "123.45");
}

TEST(MoneyTest, NormalizationLeadingZeros) {
    // Создаём через сложение, чтобы проверить нормализацию
    Money m1("0.50");
    Money m2("0.00");
    Money result = m1 + m2;
    EXPECT_EQ(result.toString(), "0.50");
}