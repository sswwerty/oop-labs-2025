#pragma once
#include "Figure.h"
#include <vector>

class Rectangle : public Figure {
public:
    Rectangle() = default;
    explicit Rectangle(const std::vector<Point>& pts);

    Rectangle(const Rectangle& other) = default;
    Rectangle(Rectangle&& other) noexcept = default;
    Rectangle& operator=(const Rectangle& other) = default;
    Rectangle& operator=(Rectangle&& other) noexcept = default;

    Point centroid() const override;
    std::vector<Point> vertices() const override;
    double area() const override;
    operator double() const override;
    std::unique_ptr<Figure> clone() const override;

    bool operator==(const Rectangle& o) const;

private:
    std::vector<Point> pts_; // size = 4
};