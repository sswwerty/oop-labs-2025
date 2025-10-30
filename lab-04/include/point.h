#ifndef POINT_H
#define POINT_H

#include <concepts>
#include <cmath>
#include <iostream>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
struct Point {
T x{};
T y{};

Point() = default;
Point(T x_, T y_) : x(x_), y(y_) {}

Point(const Point& other) = default;
Point& operator=(const Point& other) = default;

Point(Point&&) noexcept = default;
Point& operator=(Point&&) noexcept = default;

bool operator==(const Point& o) const {
return std::abs((double)(x - o.x)) < 1e-9 && std::abs((double)(y - o.y)) < 1e-9;
}

friend std::ostream& operator<<(std::ostream& os, const Point& p) {
os << "(" << p.x << ", " << p.y << ")";
return os;
}
};

#endif