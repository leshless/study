#include "longnum.hpp"
#include <iostream>

int main() {
    longnum x = longnum(6);
    longnum y = longnum(3);

    longnum z = x / y;

    std::cout << z.to_string() << std::endl;

    return 0;
}