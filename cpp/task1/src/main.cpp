#include <iostream>
#include "longnum.hpp"

int main() {
    // longnum x = longnum(1);
    // longnum y = longnum(10);
    // std::cout << x.binstring() << std::endl;
    // std::cout << y.binstring() << std::endl;

    // longnum z = x / y;

    // std::cout << z.binstring() << std::endl;

    // longnum w = z * y;

    // std::cout << w.binstring() << std::endl;


    longnum x = longnum(1);
    longnum y = longnum(3);

    longnum z = x / y;

    std::cout << z.to_string() << std::endl;

    // std::cout << (x < y) << std::endl;
    // std::cout << (x > y) << std::endl;
    // std::cout << (y > x) << std::endl;
    // std::cout << (y < x) << std::endl;

    // std::cout << (x <= y) << std::endl;
    // std::cout << (x >= y) << std::endl;

    // std::cout << (x == y) << std::endl;
    // std::cout << (x != y) << std::endl;
}