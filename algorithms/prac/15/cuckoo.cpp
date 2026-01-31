#include "cuckoo.hpp"
#include <vector>
#include <iostream>

size_t CuckooHashTable::hash1(int x) {
    return x % this->_half_cap;
}

size_t CuckooHashTable::hash2(int x) {
    return (x / this->_half_cap) % this->_half_cap;
}

size_t CuckooHashTable::size() {
    return this->_size;
}

size_t CuckooHashTable::cap() {
    return 2 * this->_half_cap;
}

void CuckooHashTable::rehash() {
    std::vector<std::optional<int>> keys1 = table1;
    std::vector<std::optional<int>> keys2 = table2;

    this->_half_cap *= 2;
    table1.clear();
    this->table1.resize(this->_half_cap);
    table2.clear();
    this->table2.resize(this->_half_cap);

    for (auto key : keys1) {
        if (key.has_value()) {
            this->insert(key.value());
        }
    }

    for (auto key : keys2) {
        if (key.has_value()) {
            this->insert(key.value());
        }
    }
}

void CuckooHashTable::insert(int key) {
    if (this->search(key)) {
        return;
    }

    size_t first_hash = this->hash1(key);
    bool f = false;

    int cur = key;
    while (true) {
        size_t hash = this->hash1(cur);

        if (!f) {
            first_hash = hash;
            f = true;
        } else if (first_hash == hash) {
            this->rehash();
            this->insert(key);
            return;
        }

        if (!this->table1[hash].has_value()) {
            this->table1[hash] = cur;
            break;
        }

        int tmp = table1[hash].value();
        table1[hash] = cur;
        cur = tmp;

        hash = this->hash2(cur);

        if (!this->table2[hash].has_value()) {
            this->table2[hash] = cur;
            break;
        }

        tmp = table2[hash].value();
        table2[hash] = cur;
        cur = tmp;
    }

    this->_size++;
}

bool CuckooHashTable::search(int key) {
    size_t hash = hash1(key);
    if ((table1[hash].has_value() && table1[hash].value() == key)) {
        return true;
    }

    hash = hash2(key);
    if ((table2[hash].has_value() && table2[hash].value() == key)) {
        return true;
    }

    return false;
}

void CuckooHashTable::print() {
    for (auto key : this->table1) {
        if (key.has_value()) {
            std::cout << key.value() << "|";
        } else {
            std::cout << "X |"; 
        }
    }
    std::cout << std::endl;
    for (auto key : this->table2) {
        if (key.has_value()) {
            std::cout << key.value() << "|";
        } else {
            std::cout << "X |"; 
        }
    }
    std::cout << std::endl;
}