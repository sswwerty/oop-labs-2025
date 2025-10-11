#include "ArrayFigures.h"
#include <stdexcept>

void ArrayFigures::add(std::unique_ptr<Figure> f) {
    arr_.push_back(std::move(f));
}

bool ArrayFigures::remove_at(size_t idx) {
    if (idx >= arr_.size()) return false;
    arr_.erase(arr_.begin() + static_cast<long>(idx));
    return true;
}

Point ArrayFigures::centroid_at(size_t idx) const {
    if (idx >= arr_.size()) throw std::out_of_range("index");
    return arr_[idx]->centroid();
}

double ArrayFigures::area_at(size_t idx) const {
    if (idx >= arr_.size()) throw std::out_of_range("index");
    return arr_[idx]->area();
}

double ArrayFigures::total_area() const {
    double s = 0.0;
    for (const auto& p : arr_) s += p->area();
    return s;
}

size_t ArrayFigures::size() const { return arr_.size(); }

const Figure& ArrayFigures::at(size_t idx) const {
    if (idx >= arr_.size()) throw std::out_of_range("idx");
    return *arr_[idx];
}

Figure& ArrayFigures::at(size_t idx) {
    if (idx >= arr_.size()) throw std::out_of_range("idx");
    return *arr_[idx];
}