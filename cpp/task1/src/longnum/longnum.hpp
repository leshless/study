#ifndef LONGNUM_HPP
#define LONGNUM_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cinttypes>
#include <climits>
#include <optional>
#include <compare>

class LongNum {
    bool sign = false;
    unsigned exp = 0;
    std::vector<uint32_t> chunks;

    LongNum(bool _sign, unsigned _exp, std::vector<uint32_t>& _chunks);

    void remove_leading_zeros();

public:
    LongNum() = default;
    LongNum(const LongNum& other) = default;
    explicit LongNum(unsigned long long x);
    LongNum(long long x);

    ~LongNum() = default;

    LongNum& operator=(const LongNum& other) = default;

    friend bool operator==(const LongNum& lhs, const LongNum& rhs);
    friend std::strong_ordering operator<=>(const LongNum& lhs, const LongNum& rhs);

    LongNum operator+() const;
    LongNum operator-() const;

    LongNum& operator<<=(unsigned shift);
    friend LongNum operator<<(const LongNum& number, unsigned shift);

    LongNum& operator>>=(unsigned shift);
    friend LongNum operator>>(const LongNum& number, unsigned shift);

    LongNum& operator+=(const LongNum& rhs);
    friend LongNum operator+(LongNum lhs, const LongNum& rhs);

    LongNum& operator-=(const LongNum& rhs);
    friend LongNum operator-(LongNum lhs, const LongNum& rhs);

    LongNum& operator*=(const LongNum& rhs);
    friend LongNum operator*(const LongNum& lhs, const LongNum& rhs);

    LongNum& operator/=(const LongNum& rhs);
    friend LongNum operator/(LongNum lhs, const LongNum& rhs);

    void set_precision(unsigned precision);
    LongNum with_precision(unsigned precision) const;

    LongNum truncate() const;
    LongNum frac() const;
    void shrink_to_fit();

    LongNum pow(unsigned power) const;
    LongNum sqrt() const;

    std::string to_binary_string() const;
    static LongNum from_binary_string(std::string str);

    std::string to_string(unsigned decimal_precision = UINT_MAX) const;
    static LongNum from_string(std::string str, const std::optional<unsigned>& precision = std::nullopt);
};

LongNum operator""_longnum(unsigned long long number);
LongNum operator""_longnum(long double number);
LongNum operator""_longnum(const char* number, std::size_t len);

std::istream& operator>>(std::istream& stream, LongNum& number);
std::ostream& operator<<(std::ostream& stream, const LongNum& number);

LongNum calculate_pi(const unsigned precision);

#endif
