#include <iostream>
#include "longnum.hpp"

int main() {
    longnum x = longnum(32);
    longnum y = longnum(32);
    std::cout << x.binstring() << std::endl;
    std::cout << y.binstring() << std::endl;

    longnum z = y * x;

    std::cout << z.binstring() << std::endl;

    // std::cout << (x < y) << std::endl;
    // std::cout << (x > y) << std::endl;
    // std::cout << (y > x) << std::endl;
    // std::cout << (y < x) << std::endl;

    // std::cout << (x <= y) << std::endl;
    // std::cout << (x >= y) << std::endl;

    // std::cout << (x == y) << std::endl;
    // std::cout << (x != y) << std::endl;
}