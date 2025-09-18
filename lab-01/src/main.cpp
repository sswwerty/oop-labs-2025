#include <iostream>
#include "box.h"

int main() {
    int l, w, h;
    std::cin >> l >> w >> h;
    std::cout << box_capacity(l, w, h) << std::endl;
    return 0;
}