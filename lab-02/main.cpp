#include <iostream>
#include "Money.h"

int main() {
    try {
        Money m1("123.45");
        Money m2("67.89");
        Money sum = m1 + m2;
        Money diff = m1 - m2;

        std::cout << "m1 = " << m1.toString() << std::endl;
        std::cout << "m2 = " << m2.toString() << std::endl;
        std::cout << "Sum = " << sum.toString() << std::endl;
        std::cout << "Diff = " << diff.toString() << std::endl;

        if (m1 > m2) {
            std::cout << "m1 is greater than m2" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}