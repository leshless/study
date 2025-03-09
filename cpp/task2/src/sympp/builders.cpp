#include <stdexcept>
#include <string>
#include <memory>
#include <complex>
#include <math.h>
#include <sstream>
#include <iostream>

#include "sympp.hpp"

namespace sympp {

// BUILDERS

template <typename T>
std::shared_ptr<expression<T>> Symbol(std::string name) {
    static_assert(std::is_same<T, long double>::value || std::is_same<T, std::complex<long double>>::value);
    return std::make_shared<symbol<T>>(name);
};

template <typename T>
std::shared_ptr<expression<T>> Number(T value) {
    static_assert(std::is_same<T, long double>::value || std::is_same<T, std::complex<long double>>::value);
    return std::make_shared<number<T>>(value);
};

template <typename T>
std::shared_ptr<expression<T>> operator+(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<add<T>>(lhs->Copy(), rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator+(std::shared_ptr<expression<T>> lhs, T rhs) {
    return std::make_shared<add<T>>(lhs->Copy(), Number<T>(rhs));
}

template <typename T>
std::shared_ptr<expression<T>> operator+(T lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<add<T>>(Number<T>(lhs), rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator-(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<sub<T>>(lhs->Copy(), rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator-(std::shared_ptr<expression<T>> lhs, T rhs) {
    return std::make_shared<sub<T>>(lhs->Copy(), Number<T>(rhs));
}

template <typename T>
std::shared_ptr<expression<T>> operator-(T lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<sub<T>>(Number<T>(lhs), rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator*(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<mul<T>>(lhs->Copy(), rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator*(std::shared_ptr<expression<T>> lhs, T rhs) {
    return std::make_shared<mul<T>>(lhs->Copy(), Number<T>(rhs));
}

template <typename T>
std::shared_ptr<expression<T>> operator*(T lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<mul<T>>(Number<T>(lhs), rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator/(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<div<T>>(lhs->Copy(), rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator/(std::shared_ptr<expression<T>> lhs, T rhs) {
    return std::make_shared<div<T>>(lhs->Copy(), Number<T>(rhs));
}

template <typename T>
std::shared_ptr<expression<T>> operator/(T lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<div<T>>(Number<T>(lhs), rhs->Copy());
}

// a^b = exp(ln(a) * b)
template <typename T>
std::shared_ptr<expression<T>> operator^(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs) {
    return Exp(Ln(lhs->Copy()) * rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator^(std::shared_ptr<expression<T>> lhs, T rhs) {
    return Exp(Ln(lhs->Copy()) * Number<T>(rhs));
}

template <typename T>
std::shared_ptr<expression<T>> operator^(T lhs, std::shared_ptr<expression<T>> rhs) {
    return Exp(Ln(Number<T>(lhs)) * rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> Ln(std::shared_ptr<expression<T>> arg) {
    return std::make_shared<ln<T>>(arg->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> Exp(std::shared_ptr<expression<T>> arg) {
    return std::make_shared<exp<T>>(arg->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> Sin(std::shared_ptr<expression<T>> arg) {
    return std::make_shared<sin<T>>(arg->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> Cos(std::shared_ptr<expression<T>> arg) {
    return std::make_shared<cos<T>>(arg->Copy());
}

template std::shared_ptr<sympp::expression<long double>> sympp::Symbol<long double>(std::string);


}
