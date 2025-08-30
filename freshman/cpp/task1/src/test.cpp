#include <iostream>
#include <algorithm>
#include <iomanip>
#include "./longnum/longnum.hpp"

const long double EPS = 1e-5;

std::string suite_name = "";
size_t test_num = 0;

void assert_equal_eps(std::string actual_string, std::string expected_string){
    test_num++;

    long double actual = std::stold(actual_string);
    long double expected = std::stold(expected_string);
    
    if (std::abs(expected - actual) < EPS){
        std::cout << "PASS: " << suite_name << " test" << test_num << std::endl;

        return;
    }

    std::cout << "FAIL: " << suite_name << " test" << test_num << std::endl;
    std::cout << std::setprecision(20) << "Expected: " << expected << "; " << "Actual: " << actual << std::endl;
}

void setup_suite(std::string name) {
    suite_name = name;
    test_num = 0;
}

void test_to_string() {
    setup_suite("to_string");

    auto x = 2392039.520934853_ln;
    assert_equal_eps(x.to_string(), "2392039.520934853");

    x = -11.6666667_ln;
    assert_equal_eps(x.to_string(), "-11.6666667");

    x = 0.00000000015_ln;
    assert_equal_eps(x.to_string(), "0.00000000015");

    x = 42.0_ln;
    assert_equal_eps(x.to_string(), "42");
}

void test_addition() {
    setup_suite("addition");
    
    auto x = 5.0_ln;
    auto y = 15.0_ln;
    assert_equal_eps((x + y).to_string(), "20");

    x = 223.13189091_ln;
    y = -23.13189091_ln;
    assert_equal_eps((x + y).to_string(), "200");

    x = 283.1729728_ln;
    y = 1.37987843874_ln;
    x.set_precision(128);

    assert_equal_eps((x + y).to_string(), "284.55285123874");
}

void test_subtraction() {
    setup_suite("subtraction");

    auto x = 15.0_ln;
    auto y = 5.0_ln;
    assert_equal_eps((x - y).to_string(), "10");

    x = 223.13189091_ln;
    y = 23.13189091_ln;
    assert_equal_eps((x - y).to_string(), "200");
}

void test_multiplication() {
    setup_suite("multiplication");

    auto x = 5.0_ln;
    auto y = 15.0_ln;
    assert_equal_eps((x * y).to_string(), "75");

    x = 223.13189091_ln;
    y = 2.0_ln;
    assert_equal_eps((x * y).to_string(), "446.26378182");
}

void test_division() {
    setup_suite("division");

    auto x = 15.0_ln;
    auto y = 5.0_ln;
    assert_equal_eps((x / y).to_string(), "3");

    x = 446.26378182_ln;
    y = 2.0_ln;
    assert_equal_eps((x / y).to_string(), "223.13189091");
}

int main() {
    test_to_string();
    test_addition();
    test_subtraction();
    test_multiplication();
    test_division();
}