#include "cuckoo.hpp"
#include <iostream>
#include <vector>

int main() {
    auto table = CuckooHashTable(10);
    
    auto values = std::vector<int>{30, 31, 15, 79, 55, 42, 99, 60, 80, 23, 43, 53};

    for (auto v : values) {
        table.insert(v);
        table.print();
        std::cout << std::endl;
    }

    return 0;
}