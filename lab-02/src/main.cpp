#include "Money.h"
#include <iostream>

int main() {
    try {
        Money m1("1250");
        Money m2("250");

        Money sum = m1.add(m2);
        Money diff = m1.subtract(m2);

        std::cout << "Первое число: " << m1.toString() << "\n";
        std::cout << "Второе число: " << m2.toString() << "\n";
        std::cout << "Сумма: " << sum.toString() << "\n";
        std::cout << "Разность: " << diff.toString() << "\n";

        // Проверка иммутабельности
        Money newSum = m1.addAssign(m2);
        std::cout << "Результат addAssign: " << newSum.toString() << "\n";
        std::cout << "Исходное m1 осталось: " << m1.toString() << "\n";

        if (m1.isGreater(m2))
            std::cout << "m1 > m2\n";
        else if (m1.isEqual(m2))
            std::cout << "m1 = m2\n";
        else
            std::cout << "m1 < m2\n";

    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}