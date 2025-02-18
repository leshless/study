#include <string>
#include <vector>

class longnum {
private:
    std::vector<uint8_t> bytes;
    size_t precision;
    uint8_t sign;

    void resize(size_t new_size);
    void lshift(size_t offset);
    void rshift(size_t offset);
    void align(longnum &other);
public:
    void set_precision(size_t new_precision);
    std::string binstring();

    longnum& operator=(const longnum& other) = default;
    longnum operator+(longnum other) const;
    longnum operator-(longnum other) const;
    // longnum& operator*(longnum other);
    // longnum& operator/(longnum other);

    friend bool operator<(const longnum& lhs, const longnum& rhs);
    friend bool operator>(const longnum& lhs, const longnum& rhs);
    friend bool operator<=(const longnum& lhs, const longnum& rhs);
    friend bool operator>=(const longnum& lhs, const longnum& rhs);
    friend bool operator!=(const longnum& lhs, const longnum& rhs);
    friend bool operator==(const longnum& lhs, const longnum& rhs);

    longnum() = default;
    longnum(uint8_t a);
    ~longnum() = default;
};
