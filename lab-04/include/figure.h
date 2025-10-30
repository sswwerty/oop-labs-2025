#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include <cmath>

template<Scalar T>
class Figure {
protected:
std::vector<std::unique_ptr<Point<T>>> pts; // владение точками

public:
Figure() = default;
// конструктор из вектора точек
Figure(std::vector<std::unique_ptr<Point<T>>>&& pts_) : pts(std::move(pts_)) {}

// копирующий конструктор
Figure(const Figure& other) {
pts.reserve(other.pts.size());
for (const auto& p : other.pts) {
pts.emplace_back(std::make_unique<Point<T>>(p->x, p->y));
}
}

Figure& operator=(const Figure& other) {
if (this == &other) return *this;
pts.clear();
pts.reserve(other.pts.size());
for (const auto& p : other.pts) {
pts.emplace_back(std::make_unique<Point<T>>(p->x, p->y));
}
return *this;
}

Figure(Figure&&) noexcept = default;
Figure& operator=(Figure&&) noexcept = default;

virtual ~Figure() = default;

// виртуальное клонирование
virtual std::unique_ptr<Figure<T>> clone() const = 0;

// площадь
virtual double area() const = 0;

// геометрический центр (среднее по координатам вершин)
virtual Point<T> center() const {
Point<T> c{};
if (pts.empty()) return c;
double sx = 0, sy = 0;
for (const auto& p : pts) { sx += (double)p->x; sy += (double)p->y; }
c.x = (T)(sx / pts.size());
c.y = (T)(sy / pts.size());
return c;
}

// печать вершин, центра и площади
virtual void print(std::ostream& os) const {
os << "Vertices: ";
for (const auto& p : pts) os << *p << " ";
os << " | Center: " << center() << " | Area: " << std::fixed << std::setprecision(6) << area();
}

// операции
explicit operator double() const { return area(); }

bool operator==(const Figure& o) const {
if (pts.size() != o.pts.size()) return false;
for (size_t i = 0; i < pts.size(); ++i) {
if (!(*pts[i] == *o.pts[i])) return false;
}
return std::abs(area() - o.area()) < 1e-9;
}
};

#endif