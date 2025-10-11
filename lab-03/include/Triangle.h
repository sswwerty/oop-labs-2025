#pragma once
#include "Figure.h"
#include <vector>

class Triangle : public Figure {
public:
    Triangle() = default;
    explicit Triangle(const std::vector<Point>& pts);

    // default копирование/перемещение
    Triangle(const Triangle& other) = default;
    Triangle(Triangle&& other) noexcept = default;
    Triangle& operator=(const Triangle& other) = default;
    Triangle& operator=(Triangle&& other) noexcept = default;

    Point centroid() const override;
    std::vector<Point> vertices() const override;
    double area() const override;
    operator double() const override;
    std::unique_ptr<Figure> clone() const override;

    bool operator==(const Triangle& o) const;

private:
    std::vector<Point> pts_; // size = 3
};