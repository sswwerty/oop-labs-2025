#include "Triangle.h"
#include <stdexcept>
#include <cmath>

Triangle::Triangle(const std::vector<Point>& pts) {
    if (pts.size() != 3) throw std::invalid_argument("Triangle requires 3 points");
    pts_ = pts;
}

Point Triangle::centroid() const {
    double cx = 0.0, cy = 0.0;
    for (const auto &p : pts_) { cx += p.x; cy += p.y; }
    return Point(cx / 3.0, cy / 3.0);
}

std::vector<Point> Triangle::vertices() const { return pts_; }

double Triangle::area() const {
    double x1 = pts_[0].x, y1 = pts_[0].y;
    double x2 = pts_[1].x, y2 = pts_[1].y;
    double x3 = pts_[2].x, y3 = pts_[2].y;
    return std::abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) * 0.5);
}

Triangle::operator double() const { return area(); }

std::unique_ptr<Figure> Triangle::clone() const {
    return std::make_unique<Triangle>(*this);
}

bool Triangle::operator==(const Triangle& o) const {
    const double eps = 1e-9;
    for (int i = 0; i < 3; ++i) {
        if (std::abs(pts_[i].x - o.pts_[i].x) > eps) return false;
        if (std::abs(pts_[i].y - o.pts_[i].y) > eps) return false;
    }
    return true;
}