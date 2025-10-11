#include "Figure.h"
#include "Triangle.h"
#include "Square.h"
#include "Rectangle.h"
#include <iomanip>
#include <string>
#include <cctype>

std::ostream& operator<<(std::ostream& os, const Figure& f) {
    auto verts = f.vertices();
    os << verts.size();
    for (const auto& p : verts) {
        os << ' ' << p;
    }
    return os;
}

std::istream& operator>>(std::istream& is, std::unique_ptr<Figure>& f) {
    std::string type;
    if (!(is >> type)) return is;
    int n;
    if (!(is >> n)) return is;

    if (n <= 0) { is.setstate(std::ios::failbit); return is; }

    std::vector<Point> pts;
    pts.resize(n);
    for (int i = 0; i < n; ++i) {
        if (!(is >> pts[i].x >> pts[i].y)) {
            is.setstate(std::ios::failbit);
            return is;
        }
    }

    // normalize type to uppercase
    for (char &c : type) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));

    if (type == "TRIANGLE" && n == 3) {
        f = std::make_unique<Triangle>(pts);
    } else if (type == "SQUARE" && n == 4) {
        f = std::make_unique<Square>(pts);
    } else if (type == "RECTANGLE" && n == 4) {
        f = std::make_unique<Rectangle>(pts);
    } else {
        is.setstate(std::ios::failbit);
    }

    return is;
}