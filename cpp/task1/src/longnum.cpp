#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "longnum.hpp"

const size_t CHUNK_SIZE = 16;
const size_t INIT_PRECISION = 64;

void longnum::resize(size_t new_size) {
    size_t size = this->chunks.size();

    if (size == new_size) {
        return;
    }else if (size > new_size) {
        throw "The new size cannot be less than previous one";
    }
    
    this->chunks.resize(new_size);
}

void longnum::lshift(size_t offset) {
    if (offset == 0) {
        return;
    }

    size_t size = this->chunks.size();
    int q = offset / CHUNK_SIZE;
    int r = offset % CHUNK_SIZE;

    // Resize here to make sure that we won't overflow
    size_t new_size = size + q + (r == 0 ? 0 : 1);
    this->resize(new_size);

    for (int i = new_size - 1; i >= 0; i--){
        // Two adjacent chunks, whe are interested in
        uint16_t lb = (i - q >= 0 ? this->chunks[i - q] : 0);
        uint16_t rb = (i - q - 1 >= 0 ? this->chunks[i - q - 1] : 0);
        
        this->chunks[i] = (lb << r) | (rb >> (CHUNK_SIZE - r));
    }   
}

void longnum::rshift(size_t offset) {
    if (offset == 0) {
        return;
    }

    size_t size = this->chunks.size();
    size_t q = offset / CHUNK_SIZE;
    size_t r = offset % CHUNK_SIZE;

    for (size_t i = 0; i < size; ++i){
        // Two adjacent chunks, whe are interested in
        uint16_t rb = (i + q < size ? this->chunks[i + q] : 0);
        uint16_t lb = (i + q + 1 < size ? this->chunks[i + q + 1] : 0);

        this->chunks[i] = (lb << (CHUNK_SIZE - r)) | (rb >> r);
    }  
}

longnum longnum::round() {
    longnum before = *this;
    before.set_precision(0);

    return before;
}

void longnum::align(longnum& other) {
    size_t precision = std::max(this->precision, other.precision);
    this->set_precision(precision);
    other.set_precision(precision);
    
    size_t size = std::max(this->chunks.size(), other.chunks.size());
    this->resize(size);
    other.resize(size);
}

bool longnum::less_abs(const longnum& other) {
    longnum a = *this;
    longnum b = other;
    a.align(b);

    for (int i = a.chunks.size()-1; i >= 0; i--){
        if (a.chunks[i] != b.chunks[i]){
            return (a.chunks[i] < b.chunks[i]);
        }
    }

    return false;
}

bool longnum::is_zero(void) {
    for (size_t i = 0; i < this->chunks.size(); ++i){
        if (this->chunks[i] != 0){
            return false;
        }
    }
    
    return true;
}

void longnum::pretify(void) {
    if (this->is_zero()){
        this->sign = 0;
    }

    size_t mn = this->precision / CHUNK_SIZE + 1;

    while (this->chunks.size() > 1 && this->chunks.size() > mn && this->chunks.back() == 0) {
        this->chunks.pop_back();
    }
}

void longnum::set_precision(size_t new_precision) {
    size_t precision = this->precision;

    size_t offset;
    if (new_precision > precision) {
        offset = new_precision - precision;
        this->lshift(offset);
    }else{
        offset = precision - new_precision;
        this->rshift(offset);
    }

    this->precision = new_precision;
}

std::string longnum::to_string(){
    longnum ten = longnum(10);

    longnum before = this->round();
    longnum after = *this - before;
    after.pretify();

    std::string before_res;
    while (!before.is_zero()) {
        longnum cur = before / ten;
        cur = cur.round();

        longnum rem = before - (cur * ten);
        before_res.push_back('0' + rem.chunks[rem.precision / CHUNK_SIZE]);

        before = cur;
    }

    if (before_res == ""){
        before_res = "0";
    }

    std::reverse(before_res.begin(), before_res.end());

    std::string after_res;
    while (!after.is_zero()) {
        longnum cur = after * ten;
        longnum rem = cur.round();

        after_res.push_back('0' + rem.chunks[rem.precision / CHUNK_SIZE]);

        after = cur - rem;
    }

    if (this->sign) {
        return "-" + before_res + "." + after_res;
    }

    return before_res + "." + after_res;
}

longnum operator-(const longnum& num) {
    longnum numc = num;
    numc.sign = !numc.sign;

    return numc;
}

longnum operator+(const longnum& lhs, const longnum& rhs) {
    longnum a = lhs;
    longnum b = rhs;
    a.align(b);
    
    if (a.sign != b.sign){
        // Subtract the one which abs value is less from the others
        if (a.less_abs(b)) {
            std::swap(a, b);
        }

        uint32_t carry = 0;
        for (size_t i = 0; i < a.chunks.size(); ++i){
            if ((uint32_t)a.chunks[i] < (uint32_t)b.chunks[i] + carry){
                a.chunks[i] = ((uint32_t)1 << CHUNK_SIZE) + (uint32_t)a.chunks[i] - (uint32_t)b.chunks[i] - carry;
                carry = 1;
            }else {
                a.chunks[i] = (uint32_t)a.chunks[i] - (uint32_t)b.chunks[i] - carry;
                carry = 0;
            }
        }
    }else {
        // Just sum second and first
        uint32_t carry = 0;
        for (size_t i = 0; i < a.chunks.size(); ++i){
            uint32_t res = (uint32_t)a.chunks[i] + (uint32_t)b.chunks[i] + carry;
            
            a.chunks[i] = (res << CHUNK_SIZE) >> CHUNK_SIZE;
            carry = res >> CHUNK_SIZE;
        }
        
        if (carry) {
            a.chunks.push_back(carry);
        }
    }

    a.pretify();

    return a;
}

longnum operator-(const longnum& lhs, const longnum& rhs) {
    // Already implemented in '+' operator
    return lhs + (-rhs);
}

longnum operator*(const longnum& lhs, const longnum& rhs) {
    longnum a = lhs;
    longnum b = rhs;
    a.align(b);

    longnum res = longnum();
    res.resize(a.chunks.size() + b.chunks.size());
    res.precision = a.precision + b.precision;
    res.sign = a.sign != b.sign;

    for (size_t i = 0; i < a.chunks.size(); ++i) {
        uint32_t carry = 0;

        for (size_t j = 0; j < b.chunks.size() || carry; ++j) {
            if (j < b.chunks.size()) {
                const uint32_t prod = (uint32_t)a.chunks[i] * (uint32_t)b.chunks[j] + (uint32_t)res.chunks[i + j] + carry;
                res.chunks[i + j] = ((prod << CHUNK_SIZE) >> CHUNK_SIZE);
                carry = prod >> CHUNK_SIZE;
            } else {
                res.chunks[i + j] += carry;
                carry = 0;
            }
        }
    }

    res.set_precision(std::max(a.precision, b.precision));
    res.pretify();

    return res;
}

longnum operator/(longnum lhs, longnum rhs) {
    if (rhs.is_zero()) {
        throw "Division by zero is not allowed";
    }

    if (lhs.is_zero()) {
        return lhs;
    }

    lhs.align(rhs);
    rhs.sign = 0;

    longnum res = longnum();
    res.resize(lhs.chunks.size());
    res.set_precision(lhs.precision);
    res.sign = lhs.sign != rhs.sign;

    longnum cur = longnum();
    
    for (int i = lhs.chunks.size() - 1; i >= 0; --i) {
        cur.lshift(CHUNK_SIZE);
        cur = cur + longnum(lhs.chunks[i]);

        uint16_t q = 0;
        while (cur >= rhs) {
            cur = cur - rhs;
            ++q;
        }
        res.chunks[i] = q;
    }

    res.pretify();
    
    return res;
}

longnum operator""_ln(long double num) {
    bool sign = (num < 0);
    num = std::abs(num);

    long long before = floor(num);
    long double after = num - before;

    std::vector<uint16_t> before_res;
    while (before > 0){
        before_res.push_back(before % (1 << CHUNK_SIZE));
        before >>= CHUNK_SIZE;
    }

    std::vector<uint16_t> after_res;
    for (size_t i = 0; i < INIT_PRECISION / CHUNK_SIZE; ++i){
        after *= (1 << CHUNK_SIZE);
        uint16_t cur = floor(after);
        after -= cur;

        after_res.push_back(cur);
    }

    std::reverse(after_res.begin(), after_res.end());

    longnum res = longnum();
    res.sign = sign;
    res.precision = INIT_PRECISION;
    res.chunks.insert(res.chunks.begin(), after_res.begin(), after_res.end());
    res.chunks.insert(res.chunks.end(), before_res.begin(), before_res.end());

    return res;
}

bool operator<(const longnum& lhs, const longnum& rhs) {
    if (lhs.sign > rhs.sign){
        return true;
    }

    if (lhs.sign < rhs.sign){
        return false;
    }

    longnum a = lhs;
    longnum b = rhs;
    a.align(b);

    for (int i = a.chunks.size()-1; i >= 0; i--){
        if (a.chunks[i] != b.chunks[i]){
            return (a.chunks[i] < b.chunks[i]) != a.sign;
        }
    }

    return false;
}

bool operator>(const longnum& lhs, const longnum& rhs) {
    return rhs < lhs;
}

bool operator<=(const longnum& lhs, const longnum& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const longnum& lhs, const longnum& rhs) {
    return !(lhs < rhs);
}

bool operator!=(const longnum& lhs, const longnum& rhs) {
    return (lhs < rhs) || (lhs < rhs);
}

bool operator==(const longnum& lhs, const longnum& rhs) {
    return !(lhs != rhs);
}

longnum::longnum(uint16_t a){
    this->chunks = std::vector<uint16_t>(INIT_PRECISION / CHUNK_SIZE + 1, 0);
    this->chunks[INIT_PRECISION / CHUNK_SIZE] = a;
    this->precision = INIT_PRECISION;
    this->sign = 0;
}
