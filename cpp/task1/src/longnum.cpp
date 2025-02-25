#include <stdlib.h>

#include <vector>
#include <algorithm>
#include <iostream>

#include "longnum.hpp"

const size_t INIT_PRECISION = 16;
const size_t INIT_LENGTH = 4;

void longnum::resize(size_t new_size) {
    size_t size = this->bytes.size();

    if (size == new_size) {
        return;
    }else if (size > new_size) {
        throw "The new size cannot be less than previous";
    }
    
    this->bytes.resize(new_size);
}

void longnum::lshift(size_t offset) {
    if (offset == 0) {
        return;
    }

    size_t size = this->bytes.size();
    size_t q = offset / 8;
    size_t r = offset % 8;

    // Resize here to make sure that we won't overflow
    size_t new_size = size + q + (r == 0 ? 0 : 1);
    this->resize(new_size);

    for (int i = new_size - 1; i >= 0; --i){
        // Two adjacent bytes, whe are interested in
        uint8_t lb = (i - q >= 0 ? this->bytes[i - q] : 0);
        uint8_t rb = (i - q - 1 >= 0 ? this->bytes[i - q - 1] : 0);

        this->bytes[i] = (lb << r) | (rb >> (8 - r));
    }   
}

void longnum::rshift(size_t offset) {
    if (offset == 0) {
        return;
    }

    size_t size = this->bytes.size();
    size_t q = offset / 8;
    size_t r = offset % 8;

    for (int i = 0; i < size; ++i){
        // Two adjacent bytes, whe are interested in
        uint8_t rb = (i + q < size ? this->bytes[i + q] : 0);
        uint8_t lb = (i + q + 1 < size ? this->bytes[i + q + 1] : 0);

        this->bytes[i] = (lb << (8 - r)) | (rb >> r);
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
    
    size_t size = std::max(this->bytes.size(), other.bytes.size());
    this->resize(size);
    other.resize(size);
}

bool longnum::less_abs(const longnum& other) {
    longnum a = *this;
    longnum b = other;
    a.align(b);

    for (int i = a.bytes.size()-1; i >= 0; i--){
        if (a.bytes[i] != b.bytes[i]){
            return (a.bytes[i] < b.bytes[i]);
        }
    }

    return false;
}

bool longnum::is_zero(void) {
    longnum zero = longnum(0);
    if (!this->less_abs(zero) && !zero.less_abs(*this)){
        return true;
    }
    
    return false;
}

void longnum::pretify(void) {
    if (this->is_zero()){
        this->sign = 0;
    }

    size_t mn = this->precision / 8 + 1;

    while (this->bytes.size() > 1 && this->bytes.size() > mn && this->bytes.back() == 0) {
        this->bytes.pop_back();
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
    // TODO: handle negative numbers

    longnum ten = longnum(10);

    longnum before = this->round();
    longnum after = *this - before;
    after.pretify();

    std::string before_res;
    while (!before.is_zero()) {
        longnum cur = before / ten;
        cur = cur.round();

        longnum rem = before - (cur * ten);
        before_res.push_back('0' + rem.bytes[rem.precision / 8]);

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

        after_res.push_back('0' + rem.bytes[rem.precision / 8]);

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

        uint16_t carry = 0;
        for (size_t i = 0; i < a.bytes.size(); ++i){
            if ((uint16_t)a.bytes[i] < (uint16_t)b.bytes[i] + carry){
                a.bytes[i] = ((uint16_t)1 << 8) + (uint16_t)a.bytes[i] - (uint16_t)b.bytes[i] - carry;
                carry = 1;
            }else {
                a.bytes[i] = (uint16_t)a.bytes[i] - (uint16_t)b.bytes[i] - carry;
                carry = 0;
            }
        }
    }else {
        // Just sum second and first
        uint16_t carry = 0;
        for (size_t i = 0; i < a.bytes.size(); ++i){
            uint16_t res = (uint16_t)a.bytes[i] + (uint16_t)b.bytes[i] + carry;
            
            a.bytes[i] = (res << 8) >> 8;
            carry = res >> 8;
        }
        
        if (carry) {
            a.bytes.push_back(carry);
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

    longnum res = longnum(0);
    res.resize(a.bytes.size() + b.bytes.size());
    res.precision = a.precision + b.precision;
    res.sign = a.sign != b.sign;

    for (size_t i = 0; i < a.bytes.size(); ++i) {
        uint16_t carry = 0;

        for (size_t j = 0; j < b.bytes.size() || carry; ++j) {
            if (j < b.bytes.size()) {
                const uint16_t prod = (uint16_t)a.bytes[i] * (uint16_t)b.bytes[j] + (uint16_t)res.bytes[i + j] + carry;
                res.bytes[i + j] = ((prod << 8) >> 8);
                carry = prod >> 8;
            } else {
                res.bytes[i + j] += carry;
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
    res.resize(lhs.bytes.size());
    res.set_precision(lhs.precision);
    res.sign = lhs.sign != rhs.sign;

    longnum cur = longnum();
    
    for (int i = lhs.bytes.size() - 1; i >= 0; --i) {
        cur.lshift(8);
        cur = cur + longnum(lhs.bytes[i]);

        uint8_t q = 0;
        while (cur >= rhs) {
            cur = cur - rhs;
            ++q;
        }
        res.bytes[i] = q;
    }

    res.pretify();
    
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

    for (int i = a.bytes.size()-1; i >= 0; i--){
        if (a.bytes[i] != b.bytes[i]){
            return (a.bytes[i] < b.bytes[i]) != a.sign;
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

longnum::longnum(uint8_t a){
    this->bytes = std::vector<uint8_t>(5, 0);
    this->bytes[4] = a;
    this->precision = 32;
    this->sign = 0;
}
