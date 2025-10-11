#include <gtest/gtest.h>
#include "Triangle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Point.h"

TEST(AreaTest, TriangleArea) {
    std::vector<Point> pts = {{0,0},{1,0},{0,1}};
    Triangle t(pts);
    EXPECT_NEAR(t.area(), 0.5, 1e-9);
    Point c = t.centroid();
    EXPECT_NEAR(c.x, 1.0/3.0, 1e-9);
    EXPECT_NEAR(c.y, 1.0/3.0, 1e-9);
}

TEST(AreaTest, SquareArea) {
    std::vector<Point> pts = {{0,0},{1,0},{1,1},{0,1}};
    Square s(pts);
    EXPECT_NEAR(s.area(), 1.0, 1e-9);
    Point c = s.centroid();
    EXPECT_NEAR(c.x, 0.5, 1e-9);
    EXPECT_NEAR(c.y, 0.5, 1e-9);
}

TEST(AreaTest, RectangleArea) {
    std::vector<Point> pts = {{0,0},{2,0},{2,1},{0,1}};
    Rectangle r(pts);
    EXPECT_NEAR(r.area(), 2.0, 1e-9);
    Point c = r.centroid();
    EXPECT_NEAR(c.x, 1.0, 1e-9);
    EXPECT_NEAR(c.y, 0.5, 1e-9);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}