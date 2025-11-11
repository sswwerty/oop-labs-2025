#include <cassert>
#include "pmr_memory.hpp"
#include "pmr_singly_list.hpp"

// лёгкий тест для сборки CI / ctest
int main() {
    FixedBlockMemoryResource r(128*1024);
    std::pmr::polymorphic_allocator<std::byte> a(&r);

    PmrSinglyList<int> L(a);
    L.push_front(1);
    L.push_front(2);
    int sum = 0;
    for (auto it = L.begin(); it != L.end(); ++it) sum += *it;
    assert(sum == 3);

    struct S { int x; double y; };
    PmrSinglyList<S> LS(a);
    LS.push_front({5, 2.5});
    LS.push_front({1, 0.5});
    assert(LS.size() == 2);

    return 0;
}
