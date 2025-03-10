#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstring>

#include "sympp/sympp.hpp"

std::string usage = "differentiator (eval|diff) <args>";
std::string eval_usage = "differentiator eval <expr> <symbol1>=<value1> <symbol2>=<value2> ...";
std::string diff_usage = "differentiator diff <expr> <symbol>";

std::pair <std::string, long double> parse_sub(std::string str) {
    auto pos = str.find("=");

    if (pos == std::string::npos) {
        std::stringstream ss;
        ss << "Usage: " << eval_usage;
        throw std::invalid_argument(ss.str());
    }

    std::string left = str.substr(0, pos);
    std::string right = str.substr(pos+1, str.size());

    long double x;
    try {
        x = stold(right);
    } catch (std::exception& e) {
        std::stringstream ss;
        ss << "Usage: " << eval_usage;
        throw std::invalid_argument(ss.str());
    }


    return {left, x};
} 

int eval(int argc, char* argv[]){
    if (argc < 3) {
        std::cout << "Usage: " << eval_usage << std::endl;
        return 1;
    }

    std::shared_ptr<sympp::expression<long double>> expr;
    try {
        expr = sympp::Parse(argv[2]);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    for (int i = 3; i < argc; ++i) {
        std::pair <std::string, long double> parsed;
        try {
            parsed = parse_sub(argv[i]);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return 1;
        }

        auto s = sympp::Symbol<long double>(parsed.first);
        auto n = sympp::Number<long double>(parsed.second);

        expr = expr->Subs(s, n);
    }

    long double res;
    try {
        res = expr->Eval();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << res << std::endl;

    return 0;
}

int diff(int argc, char* argv[]){
    if (argc != 4) {
        std::cout << "Usage: " << diff_usage << std::endl;
        return 1;
    }

    std::shared_ptr<sympp::expression<long double>> expr;
    try {
        expr = sympp::Parse(argv[2]);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::shared_ptr<sympp::expression<long double>> var;
    try {
        var = sympp::Symbol<long double>(argv[3]);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::shared_ptr<sympp::expression<long double>> diff;
    try {
        diff = expr->Diff(var);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::string res;
    try {
        res = diff->String();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    
    std::cout << res << std::endl;

    return 0;
}

int main(int argc, char* argv[]){
    if (argc < 2) {
        std::cout << "Usage: " << usage << std::endl;
        return 1;
    }

    if ((std::strcmp(argv[1], "eval") == 0) && (std::strcmp(argv[1], "diff") == 0)) {
        std::cout << "Usage: " << usage << std::endl;
        return 1;
    }

    if ((std::strcmp(argv[1], "eval") == 0)) {
        return eval(argc, argv);
    }

    return diff(argc, argv);
}