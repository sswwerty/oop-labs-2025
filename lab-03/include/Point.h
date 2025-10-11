#pragma once
#include <iostream>

struct Point {
    double x{0.0};
    double y{0.0};
    Point() = default;
    Point(double x_, double y_) : x(x_), y(y_) {}
};

std::ostream& operator<<(std::ostream& os, const Point& p);
std::istream& operator>>(std::istream& is, Point& p);