#include "./longnum/longnum.hpp"
#include <iostream>
#include <stdexcept>
#include <compare>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Specify calculation precision by providing a command line argument\n";
        return 1;
    }
    
    const std::string arg = argv[1];
    try {
        const int precision = std::stoi(arg);
        if (precision <= 0) {
            std::cerr << "Precision must be a positive number\n";
            return 1;
        }
        const LongNum pi = calculate_pi(std::max(380u, (unsigned)precision * 69 / 20 + 1));
        std::cout << pi.to_string(precision) << '\n';
        return 0;
    } catch (const std::invalid_argument& ex) {
        std::cerr << "Invalid precision: " << arg << '\n';
    } catch (const std::out_of_range& ex) {
        std::cerr << "Precision out of range: " << arg << '\n';
    }
}
