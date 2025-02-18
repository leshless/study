#include <string>
#include <vector>

class longnum {
private:
    std::vector<uint8_t> bytes;
    size_t precision;
    bool sign;

    void resize(size_t new_size);
    void lshift(size_t offset);
    void rshift(size_t offset);
    void align(longnum &other);
    bool less_abs(const longnum &other);
    void pretify(void);
public:
    void set_precision(size_t new_precision);

    longnum& operator=(const longnum& other) = default;

    friend longnum operator-(const longnum& num);
    friend longnum operator+(const longnum& lhs, const longnum& rhs);
    friend longnum operator-(const longnum& lhs, const longnum& rhs);
    friend longnum operator*(const longnum& lhs, const longnum& rhs);
    friend longnum operator/(const longnum& lhs, const longnum& rhs);

    friend bool operator<(const longnum& lhs, const longnum& rhs);
    friend bool operator>(const longnum& lhs, const longnum& rhs);
    friend bool operator<=(const longnum& lhs, const longnum& rhs);
    friend bool operator>=(const longnum& lhs, const longnum& rhs);
    friend bool operator!=(const longnum& lhs, const longnum& rhs);
    friend bool operator==(const longnum& lhs, const longnum& rhs);

    std::string binstring(); // tmp

    longnum() = default;
    longnum(uint8_t a);
    ~longnum() = default;
};
