#include <iostream>
#include <memory>
#include "Figure.h"
#include "ArrayFigures.h"

int main() {
    std::cout << "Введите фигуры (формат: TYPE n x1 y1 ...). Завершите ввод EOF (Ctrl+D/Ctrl+Z):\n";

    ArrayFigures arr;
    while (true) {
        std::unique_ptr<Figure> f;
        if (!(std::cin >> f)) break; // если EOF или ошибка
        if (!f) break;
        arr.add(std::move(f));
    }

    std::cout << "\nРезультат:\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        Point c = arr.centroid_at(i);
        double a = arr.area_at(i);
        std::cout << "Index " << i << ": centroid = " << c << ", area = " << a << "\n";
    }
    std::cout << "Total area = " << arr.total_area() << "\n";

    // Демонстрация удаления: удаляем по индексу 0 (если есть)
    if (arr.size() > 0) {
        arr.remove_at(0);
        std::cout << "После удаления первого элемента, total area = " << arr.total_area() << "\n";
    }

    return 0;
}