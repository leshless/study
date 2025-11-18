#include "bloom_filter.h"
 
BloomFilter::BloomFilter(size_t hashes, size_t bits) {
    this->_hashes = hashes;
    this->_bits = bits;
    this->_filter.resize(bits);
    this->false_positive_cnt = 0;
    this->cnt = 0;
    this->_raw_set.clear();
    this->hasher = std::hash<std::string>{};
}
 
 
void BloomFilter::add(const std::string &s) {
    for (size_t i = 0; i < this->_hashes; i++) {
        size_t hash = this->_get_hash(i, s);
        this->_filter[hash % this->_bits] = 1;
    }

    this->_raw_set.insert(s);
}

 
bool BloomFilter::verify(const std::string &s) {
    this->cnt++;

    for (size_t i = 0; i < this->_hashes; i++) {
        size_t hash = this->_get_hash(i, s);
        if (!this->_filter[hash % this->_bits]) {
            return false;
        }
    }


    if (this->_raw_set.find(s) == this->_raw_set.end()) {
        this->false_positive_cnt++;
    }

    return true;
}
 
 
double BloomFilter::getFPRate() const {
    if (this->cnt == 0) {
        return 0.0;
    }

    return (double)this->false_positive_cnt / this->cnt;
}
 
 
size_t BloomFilter::numberOfHashFunctions() const {
    return this->_hashes;
}
 
 
size_t BloomFilter::numberOfBits() const {
    return this->_bits;
}
 
 
inline size_t BloomFilter::_get_hash(int num, const std::string &s) const {
    if (num == 0) {
        return this->hasher(s);
    }

    return this->hasher(s + std::to_string(num));
}
