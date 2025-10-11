#include "Rectangle.h"
#include "Util.h"
#include <stdexcept>
#include <cmath>

Rectangle::Rectangle(const std::vector<Point>& pts) {
    if (pts.size() != 4) throw std::invalid_argument("Rectangle requires 4 points");
    pts_ = pts;
}

Point Rectangle::centroid() const {
    double cx = 0.0, cy = 0.0;
    for (const auto &p : pts_) { cx += p.x; cy += p.y; }
    return Point(cx / 4.0, cy / 4.0);
}

std::vector<Point> Rectangle::vertices() const { return pts_; }

double Rectangle::area() const {
    return polygon_area(pts_);
}

Rectangle::operator double() const { return area(); }

std::unique_ptr<Figure> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

bool Rectangle::operator==(const Rectangle& o) const {
    const double eps = 1e-9;
    for (int i = 0; i < 4; ++i) {
        if (std::abs(pts_[i].x - o.pts_[i].x) > eps) return false;
        if (std::abs(pts_[i].y - o.pts_[i].y) > eps) return false;
    }
    return true;
}