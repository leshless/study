#include <string>
#include <vector>

class longnum {
private:
    std::vector<uint8_t> bytes; // TODO: rewrite to uint_32
    size_t precision;
    bool sign;

    void resize(size_t new_size);
    void lshift(size_t offset);
    void rshift(size_t offset);
    void align(longnum &other);
    bool less_abs(const longnum &other);
    bool is_zero();
    void pretify(void);
public:
    longnum round();
    void set_precision(size_t new_precision);

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

    std::string to_string();

    longnum() = default;
    longnum(uint8_t a);
    ~longnum() = default;
};
