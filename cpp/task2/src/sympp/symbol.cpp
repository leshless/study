#include <stdexcept>
#include <string>
#include <memory>
#include <complex>
#include <math.h>
#include <sstream>
#include <iostream>

#include "sympp.hpp"

namespace sympp {

// SYMBOL

template <typename T>
symbol<T>::symbol(std::string name) {
    static_assert(std::is_same<T, long double>::value || std::is_same<T, std::complex<long double>>::value);
    this->name = name;
}

template <typename T>
expression_type symbol<T>::Type() {
    return EXPRESSION_SYMBOL;
}

template <typename T>
std::string symbol<T>::String() {
    return this->name;
}

template <typename T>
T symbol<T>::Eval() {
    throw std::invalid_argument("expression contains variable symbol " + this->name);
}

template <typename T>
std::shared_ptr<expression<T>> symbol<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    if (x->String() != this->name) {
        return Number(T(0));
    }

    return Number(T(1));
}

template <typename T>
std::shared_ptr<expression<T>> symbol<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    if (x->String() != this->name) {
        return this->Copy();
    }

    return e->Copy();
}

template <typename T>
std::shared_ptr<expression<T>> symbol<T>::Copy() {
    return std::make_shared<symbol<T>>(this->name);
}

template class symbol<long double>;
template class symbol<std::complex<long double>>;

}