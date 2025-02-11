#include <iostream>
#include "longnum.hpp"

int main() {
    auto x = longnum(131);
    std::cout << x.binstring() << std::endl;

    // longnum y = longnum(44);
    // std::cout << y.binstring() << std::endl;

    // longnum z = x + y;
    // std::cout << z.binstring() << std::endl;

    // z.set_precision(30);
    // std::cout << z.binstring() << std::endl;
}