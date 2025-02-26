#include <string>
#include <vector>

class longnum {
private:
    std::vector<uint16_t> chunks;
    size_t precision;
    bool sign;

    void resize(size_t new_size);
    void lshift(size_t offset);
    void rshift(size_t offset);
    void align(longnum &other);
    bool less_abs(const longnum &other);
    bool is_zero();
    void pretify(void);
    longnum round();
public:
    void set_precision(size_t new_precision);
    std::string to_string();

    longnum& operator=(const longnum& other) = default;

    friend longnum operator-(const longnum& num);
    friend longnum operator+(const longnum& lhs, const longnum& rhs);
    friend longnum operator-(const longnum& lhs, const longnum& rhs);
    friend longnum operator*(const longnum& lhs, const longnum& rhs);
    friend longnum operator/(longnum lhs, longnum rhs);

    friend bool operator<(const longnum& lhs, const longnum& rhs);
    friend bool operator>(const longnum& lhs, const longnum& rhs);
    friend bool operator<=(const longnum& lhs, const longnum& rhs);
    friend bool operator>=(const longnum& lhs, const longnum& rhs);
    friend bool operator!=(const longnum& lhs, const longnum& rhs);
    friend bool operator==(const longnum& lhs, const longnum& rhs);
    friend longnum operator""_ln(long double number);
    
    longnum() = default;
    longnum(uint16_t a);
    ~longnum() = default;
};

longnum operator""_ln(long double number);