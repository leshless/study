#include <stdexcept>
#include <string>
#include <memory>
#include <complex>
#include <math.h>
#include <sstream>
#include <iostream>

#include "sympp.hpp"

namespace sympp {

// NUMBER

template <typename T>
number<T>::number(T value) {
    static_assert(std::is_same<T, long double>::value || std::is_same<T, std::complex<long double>>::value);
    this->value = value;
}

template <typename T>
expression_type number<T>::Type() {
    return EXPRESSION_NUMBER;
}

template <typename T>
std::string number<T>::String() {
    std::ostringstream ss;
    ss << this->value;
    return ss.str();
}

template <typename T>
T number<T>::Eval() {
    return this->value;
}

template <typename T>
std::shared_ptr<expression<T>> number<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    return Number<T>(T(0));
}

template <typename T>
std::shared_ptr<expression<T>> number<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return this->Copy();
}

template <typename T>
std::shared_ptr<expression<T>> number<T>::Copy() {
    return std::make_shared<number<T>>(this->value);
}

template class number<long double>;

}