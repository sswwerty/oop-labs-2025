#pragma once
#include "Point.h"
#include <vector>
#include <cmath>

// shoelace formula
inline double polygon_area(const std::vector<Point>& pts) {
    double a = 0.0;
    int n = static_cast<int>(pts.size());
    if (n < 3) return 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        a += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
    }
    return std::abs(a) * 0.5;
}