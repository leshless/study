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
        throw "TODO: exception";
    }
    
    this->bytes.resize(new_size);
}

void longnum::lshift(size_t offset) {
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

void longnum::align(longnum& other) {
    size_t precision = std::max(this->precision, other.precision);
    this->set_precision(precision);
    other.set_precision(precision);
    
    size_t size = std::max(this->bytes.size(), other.bytes.size());
    this->resize(size);
    other.resize(size);
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

std::string longnum::binstring(){
    size_t size = this->bytes.size();
    size_t precision = this->precision;

    std::string res;

    for (int i = 0; i < size; i++){
        for (int j = 0; j < 8; j++){
            if (i * 8 + j == precision){
                res.push_back('.');
            }

            uint8_t b = this->bytes[i] & (1 << j);
            res.push_back(b == 0 ? '0' : '1');
        }
    }

    std::reverse(res.begin(), res.end());
    return res;
}

longnum longnum::operator+(longnum b) const{
    longnum a = *this;

    a.align(b);

    if (a.sign != b.sign){
        // Subtract
    }

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

    return a;
}

longnum longnum::operator-(longnum other) const{
    other.sign = 1;
    return *this + other;
}


bool operator<(const longnum& lhs, const longnum& rhs) {
    if (lhs.sign > rhs.sign){
        return true;
    }

    if (lhs.sign < rhs.sign){
        return false;
    }

    longnum lhsc = lhs;
    longnum rhsc = rhs;
    lhsc.align(rhsc);

    for (int i = lhsc.bytes.size(); i >= 0; i--){
        if (lhsc.bytes[i] != rhsc.bytes[i]){
            std::cout << int(lhsc.bytes[i]) << " " << int(rhsc.bytes[i]) << std::endl;
            return (lhsc.bytes[i] < rhsc.bytes[i]) != lhsc.sign;
        }
    }

    return false;
}

bool operator>(const longnum& lhs, const longnum& rhs) {
    return rhs < lhs;
}

bool operator<=(const longnum& lhs, const longnum& rhs) {
    return !(lhs < rhs);
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
    this->bytes = std::vector<uint8_t>(INIT_LENGTH, 0);
    this->bytes[2] = a;
    this->precision = INIT_PRECISION;
    this->sign = 0;
}
