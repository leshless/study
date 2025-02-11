#include <stdlib.h>

#include <vector>
#include <algorithm>

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

void longnum::set_precision(size_t new_precision){
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

longnum& longnum::operator=(const longnum& other){
    if (this == &other){
        return *this;
    }

    std::copy(other.bytes.begin(), other.bytes.end(), this->bytes);
    this->precision = other.precision;
    this->sign = other.sign;

    return *this;
}

longnum longnum::operator+(longnum& a){
    longnum& b = *this;

    size_t precision = std::max(a.precision, b.precision);
    a.set_precision(precision);
    b.set_precision(precision);
    
    size_t size = std::max(a.bytes.size(), b.bytes.size()) + 1;
    a.resize(size);
    b.resize(size);

    if (a.sign){
        if (b.sign){
            // Just sum second and first and set sign to 1

        }else{
            // Subtract first from second


        }
    
        return a;
    }
    
    if (b.sign){
        // Subtract second from first
    
        return a;
    }

    // Just sum second and first
    uint16_t carry = 0;
    for (size_t i = 0; i < size; ++i){
        uint16_t res = (uint16_t)a.bytes[i] + (uint16_t)b.bytes[i] + carry;
        
        a.bytes[i] = (res << 8) >> 8;
        carry = res >> 8;
    }

    return a;
}

longnum longnum::operator-(longnum& other){
    other.sign = 1;
    return *this + other;
}

longnum::longnum(uint8_t a){
    this->bytes = std::vector<uint8_t>(INIT_LENGTH, 0);
    this->bytes[0] = a;
    this->precision = INIT_PRECISION;
    this->sign = 0;
}
