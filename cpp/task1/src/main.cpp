#include <iostream>
#include "longnum.hpp"

int main() {
    longnum x = longnum(1);
    longnum y = longnum(2);

    std::cout << (y < x) << std::endl;
    std::cout << x.binstring() << std::endl;
    std::cout << y.binstring() << std::endl;

    std::cout << (y < x) << std::endl;
    std::cout << x.binstring() << std::endl;
    std::cout << y.binstring() << std::endl;

    std::cout << (x < y) << std::endl;
    std::cout << x.binstring() << std::endl;
    std::cout << y.binstring() << std::endl;

    std::cout << (y <= x) << std::endl;
    std::cout << x.binstring() << std::endl;
    std::cout << y.binstring() << std::endl;

    std::cout << (y <= x) << std::endl;
    std::cout << x.binstring() << std::endl;
    std::cout << y.binstring() << std::endl;
}