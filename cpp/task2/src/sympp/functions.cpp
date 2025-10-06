#include <stdexcept>
#include <string>
#include <memory>
#include <complex>
#include <math.h>
#include <sstream>
#include <iostream>

#include "sympp.hpp"

namespace sympp {


// LOGARITHM

template <typename T>
ln<T>::ln(std::shared_ptr<expression<T>> arg) {
    this->arg = arg;
}

template <typename T>
expression_type ln<T>::Type() {
    return EXPRESSION_FUNCTION;
}

template <typename T>
std::string ln<T>::String() {
    return "ln(" + this->arg->String() + ")";
}

template <typename T>
T ln<T>::Eval() {
    auto x = this->arg->Eval();

    if constexpr (std::is_same<T, long double>::value) {
        long double xr = x;

        if (xr <= 1e-10) {
            throw std::invalid_argument("non-positive real logarithm argument");
        }
    }
    if constexpr (std::is_same<T, std::complex<long double>>::value) {
        std::complex<long double> xc = x;

        if (std::abs(xc.real()) < 1e-10 && std::abs(xc.imag()) < 1e-10) {
            throw std::invalid_argument("zero complex logarithm argument");
        }
    }

    return std::log(x);
}

template <typename T>
std::shared_ptr<expression<T>> ln<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    return (Number(T(1)) / this->arg->Copy()) * this->arg->Diff(x);
}

template <typename T>
std::shared_ptr<expression<T>> ln<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return Ln(this->arg->Subs(x, e));
}

template <typename T>
std::shared_ptr<expression<T>> ln<T>::Copy() {
    return std::make_shared<ln<T>>(this->arg->Copy());
}

// EXPONENT

template <typename T>
exp<T>::exp(std::shared_ptr<expression<T>> arg) {
    this->arg = arg;
}

template <typename T>
expression_type exp<T>::Type() {
    return EXPRESSION_FUNCTION;
}

template <typename T>
std::string exp<T>::String() {
    return "exp(" + this->arg->String() + ")";
}

template <typename T>
T exp<T>::Eval() {
    return std::exp(this->arg->Eval());
}

template <typename T>
std::shared_ptr<expression<T>> exp<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    return Exp(this->arg->Copy()) * this->arg->Diff(x);
}

template <typename T>
std::shared_ptr<expression<T>> exp<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return Exp(this->arg->Subs(x, e));
}

template <typename T>
std::shared_ptr<expression<T>> exp<T>::Copy() {
    return std::make_shared<exp<T>>(this->arg->Copy());
}

// SIN

template <typename T>
sin<T>::sin(std::shared_ptr<expression<T>> arg) {
    this->arg = arg;
}

template <typename T>
expression_type sin<T>::Type() {
    return EXPRESSION_FUNCTION;
}

template <typename T>
std::string sin<T>::String() {
    return "sin(" + this->arg->String() + ")";
}

template <typename T>
T sin<T>::Eval() {
    return std::sin(this->arg->Eval());
}

template <typename T>
std::shared_ptr<expression<T>> sin<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    return Cos(this->arg->Copy()) * this->arg->Diff(x);
}

template <typename T>
std::shared_ptr<expression<T>> sin<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return Sin(this->arg->Subs(x, e));
}

template <typename T>
std::shared_ptr<expression<T>> sin<T>::Copy() {
    return std::make_shared<sin<T>>(this->arg->Copy());
}

// COS

template <typename T>
cos<T>::cos(std::shared_ptr<expression<T>> arg) {
    this->arg = arg;
}

template <typename T>
expression_type cos<T>::Type() {
    return EXPRESSION_FUNCTION;
}

template <typename T>
std::string cos<T>::String() {
    return "cos(" + this->arg->String() + ")";
}

template <typename T>
T cos<T>::Eval() {
    return std::cos(this->arg->Eval());
}

template <typename T>
std::shared_ptr<expression<T>> cos<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    return Number<T>(T(-1)) * Sin(this->arg->Copy()) * this->arg->Diff(x);
}

template <typename T>
std::shared_ptr<expression<T>> cos<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return Cos(this->arg->Subs(x, e));
}

template <typename T>
std::shared_ptr<expression<T>> cos<T>::Copy() {
    return std::make_shared<cos<T>>(this->arg->Copy());
}

template class exp<long double>;
template class ln<long double>;
template class sin<long double>;
template class cos<long double>;

template class exp<std::complex<long double>>;
template class ln<std::complex<long double>>;
template class sin<std::complex<long double>>;
template class cos<std::complex<long double>>;

}