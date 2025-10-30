#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"
#include <cmath>

// Трапеция: ожидаются вершины A,B,C,D по порядку (A-B верхнее основание, C-D нижнее)
template<Scalar T>
class Trapezoid : public Figure<T> {
public:
using Figure<T>::pts;
Trapezoid() = default;
Trapezoid(std::vector<std::unique_ptr<Point<T>>>&& pts_) : Figure<T>(std::move(pts_)) {}

std::unique_ptr<Figure<T>> clone() const override {
return std::make_unique<Trapezoid>(*this);
}

// площадь по формуле Гаусса (shoelace)
double area() const override {
if (pts.size() < 4) return 0.0;
double sum = 0.0;
for (size_t i = 0; i < pts.size(); ++i) {
const auto& p1 = *pts[i];
const auto& p2 = *pts[(i+1)%pts.size()];
sum += (double)p1.x * (double)p2.y - (double)p2.x * (double)p1.y;
}
return std::abs(sum) / 2.0;
}
};

#endif