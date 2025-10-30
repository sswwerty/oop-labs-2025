#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"
#include <cmath>

// Прямоугольник: ожидаются точки в порядке (A,B,C,D)
template<Scalar T>
class Rectangle : public Figure<T> {
public:
using Figure<T>::pts;

Rectangle() = default;

Rectangle(std::vector<std::unique_ptr<Point<T>>>&& pts_)
: Figure<T>(std::move(pts_)) {}

static Rectangle create_from_center_size(T cx, T cy, T width, T height) {
std::vector<std::unique_ptr<Point<T>>> v;
v.emplace_back(std::make_unique<Point<T>>(cx - width/2, cy - height/2));
v.emplace_back(std::make_unique<Point<T>>(cx + width/2, cy - height/2));
v.emplace_back(std::make_unique<Point<T>>(cx + width/2, cy + height/2));
v.emplace_back(std::make_unique<Point<T>>(cx - width/2, cy + height/2));
return Rectangle(std::move(v));
}

std::unique_ptr<Figure<T>> clone() const override {
return std::make_unique<Rectangle>(*this);
}

double area() const override {
if (pts.size() < 4) return 0.0;
// длины сторон AB и BC
auto d2 = [](const Point<T>& a, const Point<T>& b){
double dx = (double)a.x - b.x; double dy = (double)a.y - b.y; return std::sqrt(dx*dx + dy*dy);
};
double ab = d2(*pts[0], *pts[1]);
double bc = d2(*pts[1], *pts[2]);
return ab * bc;
}
};

#endif