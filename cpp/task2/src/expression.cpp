#include <stdexcept>

#include <expression.hpp>

using namespace sympp;

// SYMBOL

expression_type symbol::type() {
    return EXPRESSION_SYMBOL;
};

long double symbol::eval() {
    throw std::invalid_argument("expression contains variable symbol: " + this->name);
}

expression_ptr symbol::diff(expression_ptr s) {
    if (s->type() != EXPRESSION_SYMBOL) {
        throw std::invalid_argument("cannot differintiate by non-symbol expression");
    }

    if (s.get() == this) {

    }
}

// NUMBER

expression_type number::type() {
    return EXPRESSION_NUMBER;
};

long double number::eval() {
    return this->value;
}

expression_ptr number::diff(expression_ptr s) {

}