#pragma once
#include "Point.h"
#include <vector>
#include <iostream>
#include <memory>

class Figure {
public:
    virtual ~Figure() = default;

    // Основные виртуальные методы
    virtual Point centroid() const = 0;
    virtual std::vector<Point> vertices() const = 0;
    virtual double area() const = 0;

    // Требование: перегрузка приведения к double
    virtual operator double() const = 0;

    // Клон для копирования через базовый указатель
    virtual std::unique_ptr<Figure> clone() const = 0;
};

// выводит число вершин + координаты через пробелы (без типа)
std::ostream& operator<<(std::ostream& os, const Figure& f);

// читает фигуру формата: TYPE n x1 y1 x2 y2 ...
// Возвращает поток; в случае невалидного типа устанавливает failbit.
std::istream& operator>>(std::istream& is, std::unique_ptr<Figure>& f);