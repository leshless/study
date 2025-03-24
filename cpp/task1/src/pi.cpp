#include "./longnum/longnum.hpp"
#include <iostream>
#include <stdexcept>
#include <compare>

int main(int argc, char** argv) {
    
    
    const LongNum pi = calculate_pi(100u * 69 / 20 + 1);
    std::cout << pi.to_string(100) << '\n';


    return 0;
}
