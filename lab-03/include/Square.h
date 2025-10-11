#pragma once
#include "Figure.h"
#include <vector>

class Square : public Figure {
public:
    Square() = default;
    explicit Square(const std::vector<Point>& pts);

    Square(const Square& other) = default;
    Square(Square&& other) noexcept = default;
    Square& operator=(const Square& other) = default;
    Square& operator=(Square&& other) noexcept = default;

    Point centroid() const override;
    std::vector<Point> vertices() const override;
    double area() const override;
    operator double() const override;
    std::unique_ptr<Figure> clone() const override;

    bool operator==(const Square& o) const;

private:
    std::vector<Point> pts_; // size = 4
};