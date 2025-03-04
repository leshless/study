#include <stdexcept>
#include <string>
#include <memory>
#include <complex>
#include <math.h>
#include <sstream>
#include <iostream>

#include "expression.hpp"

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
    return this->left->Eval() / this->right->Eval();
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
    return std::log(this->arg->Eval());
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

// BUILDERS

template <typename T>
std::shared_ptr<expression<T>> Symbol(std::string name) {
    static_assert(std::is_same<T, long double>::value || std::is_same<T, std::complex<long double>>::value);
    return std::make_shared<symbol<T>>(name);
}

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
std::shared_ptr<expression<T>> operator-(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<sub<T>>(lhs->Copy(), rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator*(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<mul<T>>(lhs->Copy(), rhs->Copy());
}

template <typename T>
std::shared_ptr<expression<T>> operator/(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs) {
    return std::make_shared<div<T>>(lhs->Copy(), rhs->Copy());
}

// a^b = exp(ln(a) * b)
template <typename T>
std::shared_ptr<expression<T>> operator^(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs) {
    return Exp(Ln(lhs->Copy()) * rhs->Copy());
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

}

int main() {
    auto x = sympp::Symbol<long double>("x");
    auto y = sympp::Symbol<long double>("y");
    
    auto z = x + y;
    std::cout << z->String() << std::endl;
    
    auto w = z->Subs(x, sympp::Number<long double>(5))->Subs(y, sympp::Number<long double>(8));    
    
    std::cout << w->String() << std::endl;
    std::cout << w->Eval() << std::endl;

    std::cout << z->String() << std::endl;
    
    auto zdx = z->Diff(x);

    std::cout << zdx->Eval() << std::endl;

    auto div = x / y;

    std::cout << div->String() << std::endl;
    std::cout << div->Diff(x)->String() << std::endl;

    auto exp = sympp::Exp(z);

    std::cout << exp->String() << std::endl;
    std::cout << exp->Diff(x)->String() << std::endl;
    std::cout << exp->Subs(x, sympp::Number<long double>(2))->Subs(y, sympp::Number<long double>(5))->Eval() << std::endl;

    auto pow = x ^ z;

    std::cout << pow->String() << std::endl;
    std::cout << pow->Diff(x)->String() << std::endl;
    std::cout << pow->Subs(x, sympp::Number<long double>(2))->Subs(y, sympp::Number<long double>(5))->Eval() << std::endl;

    auto pi = sympp::Number<long double>(3.14);
    auto sin = sympp::Sin(pi);

    std::cout << sin->String() << std::endl;
    std::cout << sin->Eval() << std::endl;

    auto cos = sympp::Cos(x);

    std::cout << cos->String() << std::endl;
    std::cout << cos->Diff(x)->String() << std::endl;

    return 0;
}