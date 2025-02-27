#include <iostream>
#include <algorithm>
#include "longnum.hpp"

const long double EPS = 1e-16;

void assert_equal_eps(std::string actual_string, std::string expected_string, std::string message = ""){
    long double actual = std::stold(actual_string);
    long double expected = std::stold(expected_string);
    
    if (std::abs(expected - actual) < EPS){
        std::cout << "PASS: " << message << std::endl;

        return;
    }

    std::cout << "FAIL: " << message << std::endl;
    std::cout << "Expected: " << expected << "; " << "Actual: " << actual << std::endl;
}

int main() {
    longnum x;
    longnum y;

    x = 2392039.520934853_ln;
    assert_equal_eps(x.to_string(), "2392039.520934853", "Test to_string");
}