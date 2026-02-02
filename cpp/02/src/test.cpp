#include <iostream>
#include <algorithm>
#include <iomanip>

#include "./sympp/sympp.hpp"

using namespace sympp;

std::string suite_name = "";
size_t test_num = 0;
size_t total_test_num = 0;
size_t failed_test_num = 0;

const long double EPS = 1e-10;
void assert_equal_ld(long double actual, long double expected) {
    total_test_num++;
    test_num++;

    if (std::abs(expected - actual) < EPS){
        std::cout << "PASS: " << suite_name << " test" << test_num << std::endl;

        return;
    }

    std::cout << "FAIL: " << suite_name << " test" << test_num << std::endl;
    std::cout << std::setprecision(20) << "Expected: " << expected << "; " << "Actual: " << actual << std::endl;

    failed_test_num++;
}

template <typename T>
void assert_equal(T actual, T expected) {
    total_test_num++;
    test_num++;

    if (expected == actual){
        std::cout << "PASS: " << suite_name << " test" << test_num << std::endl;

        return;
    }

    std::cout << "FAIL: " << suite_name << " test" << test_num << std::endl;
    std::cout << "Expected: " << expected << "; " << "Actual: " << actual << std::endl;

    failed_test_num++;
}

void setup_suite(std::string name) {
    suite_name = name;
    test_num = 0;
}

void print_summary() {
    std::cout << "PASS: " << total_test_num -  failed_test_num << "/" << total_test_num << " tests" << std::endl;
}

void test_builders() {
    setup_suite("builders");

    auto x = Symbol<long double>("x");
    auto y = Symbol<long double>("y");
    auto _5 = Number<long double>(5.0);

    assert_equal<std::string>(x->String(), "x");
    assert_equal<std::string>(_5->String(), "5");
    assert_equal<std::string>((x + y)->String(), "(x + y)");
    assert_equal<std::string>((x - y)->String(), "(x - y)");
    assert_equal<std::string>((x * y)->String(), "x · y");
    assert_equal<std::string>((x / y)->String(), "x / y");
    assert_equal<std::string>((x ^ y)->String(), "x ^ y");
    assert_equal<std::string>(Ln(x)->String(), "ln(x)");
    assert_equal<std::string>(Exp(x)->String(), "exp(x)");
    assert_equal<std::string>(Sin(x)->String(), "sin(x)");
    assert_equal<std::string>(Cos(x)->String(), "cos(x)");
}

void test_type() {
    setup_suite("type");

    auto x = Symbol<long double>("x");
    auto y = Symbol<long double>("y");
    auto _5 = Number<long double>(5.0);

    assert_equal<expression_type>(x->Type(), EXPRESSION_SYMBOL);
    assert_equal<expression_type>(_5->Type(), EXPRESSION_NUMBER);
    assert_equal<expression_type>((x + y)->Type(), EXPRESSION_OPERATION);
    assert_equal<expression_type>((x - y)->Type(), EXPRESSION_OPERATION);
    assert_equal<expression_type>((x * y)->Type(), EXPRESSION_OPERATION);
    assert_equal<expression_type>((x / y)->Type(), EXPRESSION_OPERATION);
    assert_equal<expression_type>((x ^ y)->Type(), EXPRESSION_OPERATION);
    assert_equal<expression_type>(Ln(x)->Type(), EXPRESSION_FUNCTION);
    assert_equal<expression_type>(Exp(x)->Type(), EXPRESSION_FUNCTION);
    assert_equal<expression_type>(Sin(x)->Type(), EXPRESSION_FUNCTION);
    assert_equal<expression_type>(Cos(x)->Type(), EXPRESSION_FUNCTION);
}

void test_string() {
    setup_suite("string");

    auto x = Symbol<long double>("x");
    auto y = Symbol<long double>("y");

    assert_equal<std::string>((((x ^ 2.0L) + 1.0L) * (y * 3.33L - 11.0L))->String(), "(x ^ 2 + 1) · (y · 3.33 - 11)");
    assert_equal<std::string>((Ln(x) / Cos(y) ^ 2.0L)->String(), "ln(x) / cos(y) ^ 2");
    assert_equal<std::string>((x * Ln(Cos(Sin(Exp(y)))))->String(), "x · ln(cos(sin(exp(y))))");
}

void test_eval() {
    setup_suite("eval");

    assert_equal_ld(Number<long double>(-389132874923.3289893)->Eval(), -389132874923.3289893);
    assert_equal_ld((Number<long double>(-3) + Number<long double>(5))->Eval(), 2);
    assert_equal_ld((Number<long double>(1.999) - Number<long double>(0.999))->Eval(), 1);
    assert_equal_ld((Number<long double>(8239) * Number<long double>(85))->Eval(), 700315);
    assert_equal_ld((Number<long double>(8239) / Number<long double>(85))->Eval(), 96.9294117647);
    assert_equal_ld((Number<long double>(2) ^ Number<long double>(5))->Eval(), 32);
    assert_equal_ld(Ln(Number<long double>(7.389056098930650227230))->Eval(), 2);
    assert_equal_ld(Exp(Number<long double>(2))->Eval(), 7.389056098930650227230);
    assert_equal_ld(Sin(Number<long double>(1.5707963267948966192313216))->Eval(), 1);
    assert_equal_ld(Cos(Number<long double>(3.14159265358979))->Eval(), -1);
}

void test_diff() {
    setup_suite("diff");

    auto x = Symbol<long double>("x");
    auto y = Symbol<long double>("y");
    auto _5 = Number<long double>(5.0);

    assert_equal<std::string>(x->Diff(x)->String(), "1");
    assert_equal<std::string>(_5->Diff(x)->String(), "0");
    assert_equal<std::string>((x + y)->Diff(x)->String(), "(1 + 0)");
    assert_equal<std::string>((x - y)->Diff(y)->String(), "(0 - 1)");
    assert_equal<std::string>((x * y)->Diff(x)->String(), "(1 · y + x · 0)");
    assert_equal<std::string>((x / y)->Diff(x)->String(), "(1 · y - x · 0) / y · y");
    assert_equal<std::string>((x ^ y)->Diff(x)->String(), "exp(ln(x) · y) · (1 · y / x + ln(x) · 0)");
    assert_equal<std::string>(Ln(x)->Diff(x)->String(), "1 / x · 1");
    assert_equal<std::string>(Exp(x)->Diff(x)->String(), "exp(x) · 1");
    assert_equal<std::string>(Sin(x)->Diff(x)->String(), "cos(x) · 1");
    assert_equal<std::string>(Cos(x)->Diff(x)->String(), "-1 · sin(x) · 1");
}

void test_subs() {
    setup_suite("subs");

    auto x = Symbol<long double>("x");
    auto y = Symbol<long double>("y");
    auto _5 = Number<long double>(5.0);

    assert_equal<std::string>((x + y)->Subs(x, _5)->String(), "(5 + y)");
    assert_equal<std::string>((x + y)->Subs(x, y)->Subs(y, x)->String(), "(x + x)");
    assert_equal<std::string>(Ln(x + y)->Subs(x, _5)->Subs(y, _5)->String(), "ln((5 + 5))");
}

void test_copy() {
    setup_suite("copy");

    auto x = Symbol<long double>("x");
    auto y = Symbol<long double>("y");

    auto fx = 2.0L * x + 5.0L;

    x = x->Subs(x, y);
    
    assert_equal<std::string>(fx->String(), "(2 · x + 5)");
}

void test_parse() {
    setup_suite("parse");

    auto expr = Parse("exp(11x + 187y) / sin(1.1119) ^ (110 + .99cos(lambda))");
    assert_equal<std::string>(expr->String(), "exp(((11,0) · x + (187,0) · y)) / sin((1.1119,0)) ^ ((110,0) + (0.99,0) · cos(lambda))");
    expr = Parse("exp(x) + ln(y) - sin(z)");
    assert_equal<std::string>(expr->String(), "(exp(x) + (ln(y) - sin(z)))");
    expr = Parse("cos(x) * exp(y)");
    assert_equal<std::string>(expr->String(), "cos(x) · exp(y)");
    expr = Parse("ln(exp(x))");
    assert_equal<std::string>(expr->String(), "ln(exp(x))");
    expr = Parse("sin(3 * x + 4) / cos(y - 2)");
    assert_equal<std::string>(expr->String(), "sin(((3,0) · x + (4,0))) / cos((y - (2,0)))");
    expr = Parse("exp(ln(x) + sin(y))");
    assert_equal<std::string>(expr->String(), "exp((ln(x) + sin(y)))");
    expr = Parse("sin(x)^2 + cos(y)^3");
    assert_equal<std::string>(expr->String(), "(sin(x) ^ (2,0) + cos(y) ^ (3,0))");
    expr = Parse("2 * sin(x) + 3 * cos(y)");
    assert_equal<std::string>(expr->String(), "((2,0) · sin(x) + (3,0) · cos(y))");
    expr = Parse("ln(-1*x) + exp(-0.5*y)");
    assert_equal<std::string>(expr->String(), "(ln(((0,0) - (1,0) · x)) + exp(((0,0) - (0.5,0) · y)))");
    expr = Parse("exp(sin(x) + ln(y))");
    assert_equal<std::string>(expr->String(), "exp((sin(x) + ln(y)))");
    expr = Parse("exp(3.14 * x) + cos(2.71 * y)");
    assert_equal<std::string>(expr->String(), "(exp((3.14,0) · x) + cos((2.71,0) · y))");

}

int main() {
    test_builders();
    test_type();
    test_string();
    test_eval();
    test_diff();
    test_subs();
    test_copy();
    test_parse();

    print_summary();

    if (failed_test_num == 0) {
        return 0;
    }

    return 1;
}