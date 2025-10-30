#include <iostream>
#include <memory>
#include <string>
#include <cmath>
#include <algorithm>

#include "point.h"
#include "figure.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "array.h"

using T = double;

static std::string to_lower(std::string s) {
for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
return s;
}

int main() {
using FigPtr = std::shared_ptr<Figure<T>>;
Array<FigPtr> arr;

// названия: rectangle/прямоугольник, rhombus/ромб, trapezoid/трапеция
{
std::string name;
T x1,y1,x2,y2,x3,y3,x4,y4;
bool any_input = false;
while (true) {
if (!(std::cin >> name)) break;
if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)) {
std::cerr << "Недостаточно координат для фигуры '" << name << "'\n";
break;
}
any_input = true;
std::vector<std::unique_ptr<Point<T>>> pts;
pts.emplace_back(std::make_unique<Point<T>>(x1, y1));
pts.emplace_back(std::make_unique<Point<T>>(x2, y2));
pts.emplace_back(std::make_unique<Point<T>>(x3, y3));
pts.emplace_back(std::make_unique<Point<T>>(x4, y4));
std::string key = to_lower(name);
if (key == "rectangle" || key == "прямоугольник") {
arr.push_back(std::make_shared<Rectangle<T>>(Rectangle<T>(std::move(pts))));
} else if (key == "rhombus" || key == "ромб") {
arr.push_back(std::make_shared<Rhombus<T>>(Rhombus<T>(std::move(pts))));
} else if (key == "trapezoid" || key == "трапеция") {
arr.push_back(std::make_shared<Trapezoid<T>>(Trapezoid<T>(std::move(pts))));
} else {
std::cerr << "Неизвестная фигура: '" << name << "' (пропускаю)\n";
}
}

// Если ввода нет — демонстрационный режим
if (!any_input) {
// --- Демо: создаём несколько фигур вручную ---
auto rect = std::make_shared<Rectangle<T>>(Rectangle<T>::create_from_center_size(0.0, 0.0, 4.0, 2.0));

std::vector<std::unique_ptr<Point<T>>> trap_pts;
trap_pts.emplace_back(std::make_unique<Point<T>>(-3.0, 1.0));
trap_pts.emplace_back(std::make_unique<Point<T>>(3.0, 1.0));
trap_pts.emplace_back(std::make_unique<Point<T>>(2.0, -1.0));
trap_pts.emplace_back(std::make_unique<Point<T>>(-2.0, -1.0));
auto trap = std::make_shared<Trapezoid<T>>(std::move(trap_pts));

std::vector<std::unique_ptr<Point<T>>> rh_pts;
rh_pts.emplace_back(std::make_unique<Point<T>>(0.0, 2.0));
rh_pts.emplace_back(std::make_unique<Point<T>>(2.0, 0.0));
rh_pts.emplace_back(std::make_unique<Point<T>>(0.0, -2.0));
rh_pts.emplace_back(std::make_unique<Point<T>>(-2.0, 0.0));
auto rh = std::make_shared<Rhombus<T>>(std::move(rh_pts));

arr.push_back(rect);
arr.push_back(trap);
arr.push_back(rh);
}
}

std::cout << "Stored " << arr.size() << " figures\n\n";

double total_area = 0.0;
for (size_t i = 0; i < arr.size(); ++i) {
std::cout << "Figure #" << i << ": ";
arr[i]->print(std::cout);
std::cout << "\n";
total_area += static_cast<double>(*(arr[i]));
}
std::cout << "Total area: " << total_area << "\n";

// Удалим средний элемент для демонстрации remove_at
if (arr.size() > 1) {
arr.remove_at(1);
}

std::cout << "\nAfter remove_at(1), size=" << arr.size() << "\n";
for (size_t i = 0; i < arr.size(); ++i) {
std::cout << "Figure #" << i << ": ";
arr[i]->print(std::cout);
std::cout << "\n";
}

// Демонстрация шаблонного массива для конкретного наследника
Array<Rectangle<T>> rects;
rects.push_back(Rectangle<T>::create_from_center_size(1.0, 1.0, 2.0, 2.0));
rects.push_back(Rectangle<T>::create_from_center_size(-1.0, -1.0, 3.0, 1.0));
double rects_area = 0.0;
for (size_t i = 0; i < rects.size(); ++i) {
rects_area += rects[i].area();
}
std::cout << "\nRectangles array total area: " << rects_area << "\n";

return 0;
}