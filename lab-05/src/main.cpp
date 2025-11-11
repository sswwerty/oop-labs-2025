#include <iostream>
#include <cstdio>
#include "pmr_memory.hpp"
#include "pmr_singly_list.hpp"

// простой сложный тип
struct Person {
    int id;
    double score;
    char name[32];
};

int main() {
    std::cout << "Lab05 (student style) demo\n";

    // создаём PMR с буфером 256 KB (достаточно для тестов)
    FixedBlockMemoryResource r(256 * 1024);
    std::pmr::polymorphic_allocator<std::byte> alloc(&r);

    // список int
    PmrSinglyList<int> li(alloc);
    for (int i = 0; i < 8; ++i) li.push_front(i);
    std::cout << "ints (should be 7..0): ";
    for (auto it = li.begin(); it != li.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "\nsize = " << li.size() << "\n\n";

    // список структур Person
    PmrSinglyList<Person> lp(alloc);
    for (int i = 0; i < 4; ++i) {
        Person p;
        p.id = i;
        p.score = i * 1.1;
        std::snprintf(p.name, sizeof(p.name), "P_%d", i);
        lp.push_front(p);
    }

    std::cout << "persons:\n";
    for (auto it = lp.begin(); it != lp.end(); ++it) {
        const Person& p = *it;
        std::cout << "id=" << p.id << " score=" << p.score << " name=" << p.name << "\n";
    }

    // небольшой тест reuse: добавляем и убираем много раз
    for (int k = 0; k < 50; ++k) {
        li.push_front(k);
        li.pop_front();
    }
    std::cout << "Reuse test done (no crash means reuse likely worked).\n";

    return 0;
}
