#include "Point.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << std::fixed << std::setprecision(6) << p.x << ' ' << p.y;
    return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}