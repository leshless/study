#include <iostream>
#include "longnum.hpp"

int main() {
    longnum x = -555.3857483_ln;
    x.set_precision(64);
    std::cout << "OK" << std::endl;
    std::cout << x.to_string() << std::endl;

    longnum y = 33.137782_ln;

    std::cout << y.to_string() << std::endl;

    std::cout << (x + y).to_string() << std::endl;
    std::cout << (x - y).to_string() << std::endl;

    try{
        std::cout << (x * y).to_string() << std::endl;
    }
    catch (char const* s) {
        std::cout << s << std::endl;
    }

    try{
        std::cout << (x / 0.0_ln).to_string() << std::endl;
    }
    catch (char const* s) {
        std::cout << s << std::endl;
    }
    
    std::cout << (x / y).to_string() << std::endl;
}