#pragma once
#include "Figure.h"
#include <vector>
#include <memory>

class ArrayFigures {
public:
    void add(std::unique_ptr<Figure> f);
    bool remove_at(size_t idx); // true if removed
    Point centroid_at(size_t idx) const;
    double area_at(size_t idx) const;
    double total_area() const;
    size_t size() const;
    const Figure& at(size_t idx) const;
    Figure& at(size_t idx);
private:
    std::vector<std::unique_ptr<Figure>> arr_;
};