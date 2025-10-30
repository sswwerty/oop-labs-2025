#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"
#include <cmath>

// Ромб: ожидаются 4 вершины по порядку
template<Scalar T>
class Rhombus : public Figure<T> {
public:
    using Figure<T>::pts;

    Rhombus() = default;
    Rhombus(std::vector<std::unique_ptr<Point<T>>>&& pts_) : Figure<T>(std::move(pts_)) {}

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rhombus>(*this);
    }

    // площадь по формуле Гаусса (shoelace)
    double area() const override {
        if (pts.size() < 4) return 0.0;
        double sum = 0.0;
        for (size_t i = 0; i < pts.size(); ++i) {
            const auto& p1 = *pts[i];
            const auto& p2 = *pts[(i + 1) % pts.size()];
            sum += (double)p1.x * (double)p2.y - (double)p2.x * (double)p1.y;
        }
        return std::abs(sum) / 2.0;
    }
};

#endif


