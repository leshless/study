#include <vector>
#include <functional>
#include <optional>
#include <stdexcept>
#include <iostream>

class CuckooHashTable {
private:
    std::vector<std::optional<int>> table1;
    std::vector<std::optional<int>> table2;
    int _half_cap;
    int _size;

    size_t hash1(int x);
    size_t hash2(int x);

    void rehash();

public:
    CuckooHashTable(int n) {
        _half_cap = n;
        table1 = std::vector<std::optional<int>>(_half_cap);
        table2 = std::vector<std::optional<int>>(_half_cap);
    };
    
    size_t size();
    size_t cap();

    void insert(int key);
    bool search(int key);

    void print();

    ~CuckooHashTable() = default;
};
