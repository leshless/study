#include <stdexcept>
#include <string>
#include <memory>
#include <complex>
#include <math.h>
#include <sstream>
#include <iostream>

#include "sympp.hpp"

namespace sympp {


// ADD

template <typename T>
add<T>::add(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right) {
    this->left = left;
    this->right = right;
}

template <typename T>
expression_type add<T>::Type() {
    return EXPRESSION_OPERATION;
}

template <typename T>
std::string add<T>::String() {
    return "(" + this->left->String() + " + " + this->right->String() + ")";
}

template <typename T>
T add<T>::Eval() {
    return this->left->Eval() + this->right->Eval();
}

template <typename T>
std::shared_ptr<expression<T>> add<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    return this->left->Diff(x) + this->right->Diff(x);
}

template <typename T>
std::shared_ptr<expression<T>> add<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return this->left->Subs(x, e) + this->right->Subs(x, e);
}

template <typename T>
std::shared_ptr<expression<T>> add<T>::Copy() {
    return std::make_shared<add<T>>(this->left->Copy(), this->right->Copy());
}

// SUBTRACT

template <typename T>
sub<T>::sub(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right) {
    this->left = left;
    this->right = right;
}

template <typename T>
expression_type sub<T>::Type() {
    return EXPRESSION_OPERATION;
}

template <typename T>
std::string sub<T>::String() {
    return "(" + this->left->String() + " - " + this->right->String() + ")";
}

template <typename T>
T sub<T>::Eval() {
    return this->left->Eval() - this->right->Eval();
}

template <typename T>
std::shared_ptr<expression<T>> sub<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    return this->left->Diff(x) - this->right->Diff(x);
}

template <typename T>
std::shared_ptr<expression<T>> sub<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return this->left->Subs(x, e) - this->right->Subs(x, e);
}

template <typename T>
std::shared_ptr<expression<T>> sub<T>::Copy() {
    return std::make_shared<sub<T>>(this->left->Copy(), this->right->Copy());
}

// MULTIPLY

template <typename T>
mul<T>::mul(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right) {
    this->left = left;
    this->right = right;
}

template <typename T>
expression_type mul<T>::Type() {
    return EXPRESSION_OPERATION;
}

template <typename T>
std::string mul<T>::String() {
    return this->left->String() + " · " + this->right->String();
}

template <typename T>
T mul<T>::Eval() {
    return this->left->Eval() * this->right->Eval();
}

template <typename T>
std::shared_ptr<expression<T>> mul<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    return this->left->Diff(x) * this->right->Copy() + this->left->Copy() * this->right->Diff(x);
}

template <typename T>
std::shared_ptr<expression<T>> mul<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return this->left->Subs(x, e) * this->right->Subs(x, e);
}

template <typename T>
std::shared_ptr<expression<T>> mul<T>::Copy() {
    return std::make_shared<mul<T>>(this->left->Copy(), this->right->Copy());
}

// DIVIDE

template <typename T>
div<T>::div(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right) {
    this->left = left;
    this->right = right;
}

template <typename T>
expression_type div<T>::Type() {
    return EXPRESSION_OPERATION;
}

template <typename T>
std::string div<T>::String() {
    return this->left->String() + " / " + this->right->String();
}

template <typename T>
T div<T>::Eval() {
    auto x = this->right->Eval();

    if constexpr (std::is_same<T, long double>::value) {
        long double xr = x;
        
        if (xr <= 1e-10) {
            throw std::invalid_argument("division by zero");
        }
    }
    if constexpr (std::is_same<T, std::complex<long double>>::value) {
        std::complex<long double> xc = x;
      
        if (std::abs(xc.real()) < 1e-10 && std::abs(xc.imag()) < 1e-10) {
            throw std::invalid_argument("division by zero");
        }
    }


    return this->left->Eval() / x;
}

template <typename T>
std::shared_ptr<expression<T>> div<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    return (this->left->Diff(x) * this->right->Copy() - this->left->Copy() * this->right->Diff(x)) / (this->right->Copy() * this->right->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> div<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return this->left->Subs(x, e) / this->right->Subs(x, e);
}

template <typename T>
std::shared_ptr<expression<T>> div<T>::Copy() {
    return std::make_shared<div<T>>(this->left->Copy(), this->right->Copy());
}

// POWER

template <typename T>
pow<T>::pow(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right) {
    this->left = left;
    this->right = right;
}

template <typename T>
expression_type pow<T>::Type() {
    return EXPRESSION_OPERATION;
}

template <typename T>
std::string pow<T>::String() {
    return this->left->String() + " ^ " + this->right->String();
}

template <typename T>
T pow<T>::Eval() {
    return std::pow(this->left->Eval(), this->right->Eval());
}

template <typename T>
std::shared_ptr<expression<T>> pow<T>::Diff(std::shared_ptr<expression<T>> x) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot differintiate by non-symbol expression " + this->String());
    }

    // a ^ b = e ^ (ln(a) * b) = e ^ (ln(a) * b) * (1/a * a' * b + b' * ln(a))
    return Exp(Ln(this->left->Copy()) * this->right->Copy()) * 
    (this->left->Diff(x) * this->right->Copy() / this->left->Copy() + Ln(this->left->Copy()) * this->right->Diff(x));
}

template <typename T>
std::shared_ptr<expression<T>> pow<T>::Subs(std::shared_ptr<expression<T>> x, std::shared_ptr<expression<T>> e) {
    if (x->Type() != EXPRESSION_SYMBOL){
        throw std::invalid_argument("cannot substitude non-symbol expression " + this->String());
    }

    return this->left->Subs(x, e) ^ this->right->Subs(x, e);
}

template <typename T>
std::shared_ptr<expression<T>> pow<T>::Copy() {
    return std::make_shared<pow<T>>(this->left->Copy(), this->right->Copy());
}

template class add<long double>;
template class sub<long double>;
template class mul<long double>;
template class div<long double>;
template class pow<long double>;

template class add<std::complex<long double>>;
template class sub<std::complex<long double>>;
template class mul<std::complex<long double>>;
template class div<std::complex<long double>>;
template class pow<std::complex<long double>>;

}