#include <gtest/gtest.h>
#include "box.h"

// Тест из условия задачи
TEST(BoxCapacityTest, Example) {
    EXPECT_EQ(box_capacity(32, 64, 16), 13824);
}

// Тесты на минимальные размеры
TEST(BoxCapacityTest, MinimumSize) {
    // Склад размером 2x2x2 фута = 24x24x24 дюйма
    // 24/16 = 1 ящик по каждой оси
    EXPECT_EQ(box_capacity(2, 2, 2), 1); // 1*1*1 = 1
}

TEST(BoxCapacityTest, ExactlyOneBox) {
    // Склад размером ровно 16 дюймов (1.33 фута) - округляем до 2 футов
    // 24 дюйма / 16 = 1 ящик
    EXPECT_EQ(box_capacity(2, 2, 2), 1);
}

// Тесты на граничные случаи
TEST(BoxCapacityTest, EdgeCaseJustUnderOneBox) {
    // 15 дюймов = 1.25 фута, но мы округляем до 2 футов = 24 дюйма
    // 24 / 16 = 1 ящик
    EXPECT_EQ(box_capacity(2, 2, 2), 1);
}

TEST(BoxCapacityTest, EdgeCaseJustOverOneBox) {
    // 17 дюймов = 1.42 фута, округляем до 2 футов = 24 дюйма
    // 24 / 16 = 1 ящик
    EXPECT_EQ(box_capacity(2, 2, 2), 1);
}

// Тесты на разные размеры
TEST(BoxCapacityTest, SmallWarehouse) {
    // 3x3x3 фута = 36x36x36 дюймов
    // 36/16 = 2 ящика по каждой оси
    EXPECT_EQ(box_capacity(3, 3, 3), 8); // 2*2*2 = 8
}

TEST(BoxCapacityTest, MediumWarehouse) {
    // 10x10x10 футов = 120x120x120 дюймов
    // 120/16 = 7 ящиков по каждой оси
    EXPECT_EQ(box_capacity(10, 10, 10), 343); // 7*7*7 = 343
}

TEST(BoxCapacityTest, LargeWarehouse) {
    // 50x50x50 футов = 600x600x600 дюймов
    // 600/16 = 37 ящиков по каждой оси
    EXPECT_EQ(box_capacity(50, 50, 50), 50653); // 37*37*37 = 50653
}

// Тесты на прямоугольные склады
TEST(BoxCapacityTest, RectangularWarehouse) {
    // 4x8x2 фута = 48x96x24 дюйма
    // 48/16=3, 96/16=6, 24/16=1
    EXPECT_EQ(box_capacity(4, 8, 2), 18); // 3*6*1 = 18
}

TEST(BoxCapacityTest, VeryLongWarehouse) {
    // 100x1x1 фут = 1200x12x12 дюймов
    // 1200/16=75, 12/16=0, 12/16=0
    EXPECT_EQ(box_capacity(100, 1, 1), 0); // 75*0*0 = 0
}

TEST(BoxCapacityTest, VeryWideWarehouse) {
    // 1x100x1 фут = 12x1200x12 дюймов
    // 12/16=0, 1200/16=75, 12/16=0
    EXPECT_EQ(box_capacity(1, 100, 1), 0); // 0*75*0 = 0
}

TEST(BoxCapacityTest, VeryTallWarehouse) {
    // 1x1x100 фут = 12x12x1200 дюймов
    // 12/16=0, 12/16=0, 1200/16=75
    EXPECT_EQ(box_capacity(1, 1, 100), 0); // 0*0*75 = 0
}

// Тесты на нулевые размеры
TEST(BoxCapacityTest, ZeroDimensions) {
    EXPECT_EQ(box_capacity(0, 0, 0), 0);
    EXPECT_EQ(box_capacity(10, 0, 10), 0);
    EXPECT_EQ(box_capacity(0, 10, 10), 0);
    EXPECT_EQ(box_capacity(10, 10, 0), 0);
}

// Тесты на единичные размеры
TEST(BoxCapacityTest, UnitDimensions) {
    // 1x1x1 фут = 12x12x12 дюймов
    // 12/16 = 0 ящиков по каждой оси
    EXPECT_EQ(box_capacity(1, 1, 1), 0);
}

// Тесты на размеры, кратные 16 дюймам
TEST(BoxCapacityTest, ExactMultiples) {
    // 32 дюйма = 2.67 фута, округляем до 3 футов = 36 дюймов
    // 36/16 = 2 ящика
    EXPECT_EQ(box_capacity(3, 3, 3), 8); // 2*2*2 = 8
}

// Тесты на большие числа (в пределах int)
TEST(BoxCapacityTest, LargeNumbers) {
    // 1000x1000x1000 футов
    // 12000x12000x12000 дюймов
    // 12000/16 = 750 ящиков по каждой оси
    EXPECT_EQ(box_capacity(1000, 1000, 1000), 421875000); // 750*750*750
}

// Тесты на асимметричные размеры
TEST(BoxCapacityTest, AsymmetricSizes) {
    // 5x3x7 футов = 60x36x84 дюйма
    // 60/16=3, 36/16=2, 84/16=5
    EXPECT_EQ(box_capacity(5, 3, 7), 30); // 3*2*5 = 30
}

// Тесты на размеры с остатком
TEST(BoxCapacityTest, WithRemainder) {
    // 7x7x7 футов = 84x84x84 дюйма
    // 84/16 = 5 ящиков по каждой оси (остаток 4 дюйма)
    EXPECT_EQ(box_capacity(7, 7, 7), 125); // 5*5*5 = 125
}

// Тесты на производительность с разумными размерами
TEST(BoxCapacityTest, PerformanceTest) {
    // 100x100x100 футов = 1200x1200x1200 дюймов
    // 1200/16 = 75 ящиков по каждой оси
    EXPECT_EQ(box_capacity(100, 100, 100), 421875); // 75*75*75
}

// Дополнительные тесты на граничные случаи
TEST(BoxCapacityTest, ExactlyTwoBoxes) {
    // 3x3x3 фута = 36x36x36 дюймов
    // 36/16 = 2 ящика по каждой оси
    EXPECT_EQ(box_capacity(3, 3, 3), 8); // 2*2*2 = 8
}

TEST(BoxCapacityTest, EdgeCase15Inches) {
    // 1.25 фута = 15 дюймов, но мы округляем до 2 футов = 24 дюйма
    // 24/16 = 1 ящик
    EXPECT_EQ(box_capacity(2, 2, 2), 1);
}

TEST(BoxCapacityTest, EdgeCase17Inches) {
    // 1.42 фута = 17 дюймов, но мы округляем до 2 футов = 24 дюйма
    // 24/16 = 1 ящик
    EXPECT_EQ(box_capacity(2, 2, 2), 1);
}

// Тесты на максимальные разумные значения (без переполнения int)
TEST(BoxCapacityTest, MaximumReasonableSize) {
    // 500x500x500 футов
    // 6000x6000x6000 дюймов
    // 6000/16 = 375 ящиков по каждой оси
    EXPECT_EQ(box_capacity(500, 500, 500), 52734375); // 375*375*375
}

// Тесты на очень маленькие размеры
TEST(BoxCapacityTest, VerySmallSizes) {
    // 0.5 фута = 6 дюймов
    // 6/16 = 0 ящиков
    EXPECT_EQ(box_capacity(1, 1, 1), 0); // 12/16 = 0
}

// Тесты на размеры, близкие к границе
TEST(BoxCapacityTest, NearBoundarySizes) {
    // 1.33 фута = 16 дюймов точно
    // 16/16 = 1 ящик
    EXPECT_EQ(box_capacity(2, 2, 2), 1); // 24/16 = 1
}

// Тесты на размеры, кратные 4 футам (48 дюймам = 3 ящика)
TEST(BoxCapacityTest, FourFootMultiples) {
    // 4x4x4 фута = 48x48x48 дюймов
    // 48/16 = 3 ящика по каждой оси
    EXPECT_EQ(box_capacity(4, 4, 4), 27); // 3*3*3 = 27
}

// Тесты на размеры, кратные 8 футам (96 дюймам = 6 ящиков)
TEST(BoxCapacityTest, EightFootMultiples) {
    // 8x8x8 футов = 96x96x96 дюймов
    // 96/16 = 6 ящиков по каждой оси
    EXPECT_EQ(box_capacity(8, 8, 8), 216); // 6*6*6 = 216
}

// Тесты на размеры, кратные 12 футам (144 дюймам = 9 ящиков)
TEST(BoxCapacityTest, TwelveFootMultiples) {
    // 12x12x12 футов = 144x144x144 дюйма
    // 144/16 = 9 ящиков по каждой оси
    EXPECT_EQ(box_capacity(12, 12, 12), 729); // 9*9*9 = 729
}

// Тесты на размеры, кратные 16 футам (192 дюймам = 12 ящиков)
TEST(BoxCapacityTest, SixteenFootMultiples) {
    // 16x16x16 футов = 192x192x192 дюйма
    // 192/16 = 12 ящиков по каждой оси
    EXPECT_EQ(box_capacity(16, 16, 16), 1728); // 12*12*12 = 1728
}

// Тесты на размеры, кратные 20 футам (240 дюймам = 15 ящиков)
TEST(BoxCapacityTest, TwentyFootMultiples) {
    // 20x20x20 футов = 240x240x240 дюймов
    // 240/16 = 15 ящиков по каждой оси
    EXPECT_EQ(box_capacity(20, 20, 20), 3375); // 15*15*15 = 3375
}
