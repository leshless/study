#include "longnum.hpp"
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <compare>
#include <bit>

constexpr unsigned BASE = 32;
constexpr unsigned DEFAULT_PRECISION = 64;

LongNum::LongNum(const bool _sign, const unsigned _exp, std::vector<uint32_t>& _chunks)
    : sign(_sign),
      exp(_exp),
      chunks(std::move(_chunks)) {
}

LongNum::LongNum(unsigned long long x) {
    if (x == 0) {
        return;
    }
    while (x) {
        chunks.push_back(x & UINT32_MAX);
        x >>= BASE;
    }
}

LongNum::LongNum(long long x) {
    if (x == 0) {
        return;
    }
    sign = x < 0;
    x = std::abs(x);
    while (x) {
        chunks.push_back(x & UINT32_MAX);
        x >>= BASE;
    }
}

bool operator==(const LongNum& lhs, const LongNum& rhs) {
    if (lhs.chunks.empty() || rhs.chunks.empty()) {  // when lhs = 0 or rhs = 0
        return lhs.chunks.empty() && rhs.chunks.empty();
    }
    if (lhs.sign != rhs.sign) {
        return false;
    }
    if (lhs.exp < rhs.exp) {
        return lhs.with_precision(rhs.exp) == rhs;
    }
    if (lhs.exp > rhs.exp) {
        return lhs == rhs.with_precision(lhs.exp);
    }
    return lhs.chunks == rhs.chunks;
}

std::strong_ordering operator<=>(const LongNum& lhs, const LongNum& rhs) {
    if (lhs.chunks.empty() && rhs.chunks.empty()) {  // lhs = rhs = 0
        return std::strong_ordering::equal;
    }
    if (lhs.chunks.empty()) {  // lhs = 0
        return rhs.sign ? std::strong_ordering::greater : std::strong_ordering::less;
    }
    if (rhs.chunks.empty()) {  // rhs = 0
        return lhs.sign ? std::strong_ordering::less : std::strong_ordering::greater;
    }
    if (lhs.sign && !rhs.sign) {
        return std::strong_ordering::less;
    }
    if (!lhs.sign && rhs.sign) {
        return std::strong_ordering::greater;
    }
    if (lhs.exp < rhs.exp) {
        return lhs.with_precision(rhs.exp) <=> rhs;
    }
    if (lhs.exp > rhs.exp) {
        return lhs <=> rhs.with_precision(lhs.exp);
    }
    if (lhs.chunks.size() < rhs.chunks.size()) {
        return lhs.sign ? std::strong_ordering::greater : std::strong_ordering::less;
    }
    if (lhs.chunks.size() > rhs.chunks.size()) {
        return lhs.sign ? std::strong_ordering::less : std::strong_ordering::greater;
    }
    for (size_t i = 0; i < lhs.chunks.size(); i++) {
        if (lhs.chunks[i] < rhs.chunks[i]) {
            return lhs.sign ? std::strong_ordering::greater : std::strong_ordering::less;
        }
        if (lhs.chunks[i] > rhs.chunks[i]) {
            return lhs.sign ? std::strong_ordering::less : std::strong_ordering::greater;
        }
    }
    return std::strong_ordering::equal;
}

LongNum LongNum::operator+() const {
    return *this;
}

LongNum LongNum::operator-() const {
    LongNum res(*this);
    if (*this != 0) {  // -0 must be +0
        res.sign ^= 1;
    }
    return res;
}

LongNum& LongNum::operator<<=(const unsigned shift) {
    *this = *this << shift;
    return *this;
}

LongNum operator<<(const LongNum& number, const unsigned shift) {
    if (!shift || number == 0) {
        return number;
    }
    const unsigned zeros_cnt = (shift + BASE - 1) / BASE;
    const unsigned r = shift % BASE;
    std::vector<uint32_t> chunks(number.chunks.size() + zeros_cnt, 0);
    for (size_t i = zeros_cnt; i < chunks.size(); i++) {
        chunks[i] = number.chunks[i - zeros_cnt];
    }
    if (r) {
        for (size_t i = zeros_cnt - 1; i < chunks.size() - 1; i++) {
            chunks[i] = (chunks[i] >> (BASE - r)) | (chunks[i + 1] << r);
        }
        chunks.back() >>= BASE - r;
    }
    LongNum res(number.sign, number.exp, chunks);
    res.remove_leading_zeros();
    return res;
}

LongNum& LongNum::operator>>=(const unsigned shift) {
    *this = *this >> shift;
    return *this;
}

LongNum operator>>(const LongNum& number, const unsigned shift) {
    if (!shift || number == 0) {
        return number;
    }
    const unsigned to_erase = shift / BASE;
    if (to_erase >= number.chunks.size()) {
        return (0_ln).with_precision(number.exp);
    }
    std::vector<uint32_t> chunks(number.chunks.size() - to_erase);
    const unsigned r = shift % BASE;
    for (size_t i = 0; i < chunks.size(); i++) {
        chunks[i] = number.chunks[i + to_erase];
    }
    if (r) {
        for (size_t i = 0; i < chunks.size() - 1; i++) {
            chunks[i] = (chunks[i] >> r) | (chunks[i + 1] << (BASE - r));
        }
        chunks.back() >>= r;
    }
    LongNum res(number.sign, number.exp, chunks);
    res.remove_leading_zeros();
    return res;
}

LongNum& LongNum::operator+=(const LongNum& rhs) {
    if (*this == 0) {
        *this = rhs.with_precision(std::max(exp, rhs.exp));
        return *this;
    }
    if (rhs == 0) {
        set_precision(std::max(exp, rhs.exp));
        return *this;
    }
    if (sign != rhs.sign) {
        *this -= -rhs;
        return *this;
    }
    if (exp < rhs.exp) {
        set_precision(rhs.exp);
    } else if (exp > rhs.exp) {
        *this += rhs.with_precision(exp);  // recursive call, this can only happen once
        return *this;
    }
    unsigned carry = 0;
    for (size_t i = 0; i < std::max(chunks.size(), rhs.chunks.size()) || carry; i++) {
        if (i == chunks.size()) {
            chunks.push_back(0);
        }
        const uint64_t sum = (uint64_t)chunks[i] + carry + (i < rhs.chunks.size() ? rhs.chunks[i] : 0);
        chunks[i] = sum;
        carry = sum >> BASE;
    }
    return *this;
}

LongNum operator+(LongNum lhs, const LongNum& rhs) {
    lhs += rhs;
    return lhs;
}

LongNum& LongNum::operator-=(const LongNum& rhs) {
    if (rhs == 0) {
        set_precision(std::max(exp, rhs.exp));
        return *this;
    }
    if (*this == rhs) {
        *this = (0_ln).with_precision(std::max(exp, rhs.exp));
        return *this;
    }
    if (sign != rhs.sign) {
        *this += -rhs;
        return *this;
    }
    if ((*this < rhs) ^ sign) {  // handle cases like -1 - (-2) and 1 - 2
        *this = -(rhs - *this);
        return *this;
    }
    if (exp < rhs.exp) {
        set_precision(rhs.exp);
    } else if (exp > rhs.exp) {
        *this -= rhs.with_precision(exp);  // recursive call, this can only happen once
        return *this;
    }
    unsigned carry = 0;
    for (size_t i = 0; i < rhs.chunks.size() || carry; i++) {
        if (i < rhs.chunks.size()) {
            const unsigned new_carry = chunks[i] < rhs.chunks[i] || (chunks[i] == rhs.chunks[i] && carry);  // TODO: optimize carry calculation here
            chunks[i] -= rhs.chunks[i] + carry;
            carry = new_carry;
        } else {
            chunks[i] -= carry;
            carry = (chunks[i] == UINT32_MAX);
        }
    }
    remove_leading_zeros();
    return *this;
}

LongNum operator-(LongNum lhs, const LongNum& rhs) {
    lhs -= rhs;
    return lhs;
}

LongNum& LongNum::operator*=(const LongNum& rhs) {
    *this = *this * rhs;
    return *this;
}

LongNum operator*(const LongNum& lhs, const LongNum& rhs) {
    if (lhs == 0 || rhs == 0) {
        return (0_ln).with_precision(std::max(lhs.exp, rhs.exp));
    }
    LongNum res;
    res.exp = lhs.exp + rhs.exp;
    res.chunks.resize(lhs.chunks.size() + rhs.chunks.size());
    for (size_t i = 0; i < lhs.chunks.size(); i++) {
        uint32_t carry = 0;
        for (size_t j = 0; j < rhs.chunks.size() || carry; j++) {
            if (j < rhs.chunks.size()) {
                const uint64_t cur = (uint64_t)lhs.chunks[i] * rhs.chunks[j] + res.chunks[i + j] + carry;
                res.chunks[i + j] = cur;
                carry = cur >> BASE;
            } else {
                res.chunks[i + j] += carry;
                carry = 0;
            }
        }
    }
    res.remove_leading_zeros();
    res.set_precision(std::max(lhs.exp, rhs.exp));
    res.sign = lhs.sign ^ rhs.sign;
    return res;
}

LongNum& LongNum::operator/=(const LongNum& rhs) {
    *this = *this / rhs;
    return *this;
}

LongNum operator/(LongNum lhs, const LongNum& rhs) {
    auto div_one_digit = [](const LongNum& a, const LongNum& b, LongNum& res) {
        // divide a / b as integers (ignoring exp and sign), len(b) = 1

        res = a;
        unsigned carry = 0;
        for (size_t i = res.chunks.size() - 1; i != (size_t)-1; i--) {
            const uint64_t cur = res.chunks[i] + ((uint64_t)carry << BASE);
            res.chunks[i] = cur / b.chunks.front();
            carry = cur - res.chunks[i] * b.chunks.front();
        }
    };

    auto long_div = [](LongNum u_num, LongNum v_num, LongNum& res) {
        // source: https://skanthak.hier-im-netz.de/division.html
        // divide a / b as integers (ignoring exp and sign), a >= b, len(b) >= 2

        const size_t m = u_num.chunks.size(), n = v_num.chunks.size();  // initial sizes
        const unsigned s = std::countl_zero(v_num.chunks.back());  // normalization (make first bit of divisor set to 1)
        u_num <<= s;
        v_num <<= s;
        std::vector<uint32_t>& u = u_num.chunks;
        if (u.size() == m) {
            u.push_back(0);
        }
        const std::vector<uint32_t>& v = v_num.chunks;

        res.chunks.resize(m - n + 1);
        std::vector<uint32_t>& q = res.chunks;
        for (size_t j = m - n; j != (size_t)-1; j--) {
            uint64_t qhat = (((uint64_t)u[j + n] << BASE) | u[j + n - 1]) / v[n - 1];
            uint64_t rhat = (((uint64_t)u[j + n] << BASE) | u[j + n - 1]) - qhat * v[n - 1];
            for (size_t i = 0; i < 2; i++) {
                if (qhat >= (1ull << BASE) || qhat * v[n - 2] > ((rhat << BASE) | u[j + n - 2])) {
                    qhat--;
                    rhat += v[n - 1];
                    if (rhat >= (1ull << BASE)) {
                        break;
                    }
                } else {
                    break;
                }
            }
            int64_t t;
            uint64_t carry = 0;
            for (size_t i = 0; i < n; i++) {
                const uint64_t prod = qhat * v[i];
                t = (int64_t)(u[i + j] - carry - (prod & UINT32_MAX));
                u[i + j] = t;
                carry = (prod >> BASE) - (t >> BASE);
            }
            t = (int64_t)(u[j + n] - carry);
            u[j + n] = t;

            q[j] = qhat;
            if (t < 0) {  // if we subtracted too much, add back
                q[j]--;
                carry = 0;
                for (size_t i = 0; i < n; i++) {
                    t = (int64_t)(u[i + j] + v[i] + carry);
                    u[i + j] = t;
                    carry = t >> BASE;
                }
                u[j + n] += carry;
            }
        }
    };

    if (rhs == 0) {
        throw std::invalid_argument("Division by zero");
    }
    if (lhs == 0) {
        return (0_ln).with_precision(std::max(lhs.exp, rhs.exp));
    }
    if (lhs.exp < rhs.exp) {
        lhs <<= 2 * rhs.exp - lhs.exp;
    } else {
        lhs <<= rhs.exp;
    }
    if (lhs.chunks.size() < rhs.chunks.size() ||
        (lhs.chunks.size() == rhs.chunks.size() && lhs.chunks.back() < rhs.chunks.back())) {
        return (0_ln).with_precision(std::max(lhs.exp, rhs.exp));
    }
    LongNum res;
    if (rhs.chunks.size() == 1) {
        div_one_digit(lhs, rhs, res);
    } else {
        long_div(lhs, rhs, res);
    }
    res.exp = std::max(lhs.exp, rhs.exp);
    res.sign = lhs.sign ^ rhs.sign;
    res.remove_leading_zeros();
    return res;
}

void LongNum::set_precision(const unsigned precision) {
    if (exp < precision) {
        *this <<= precision - exp;
    } else if (exp > precision) {
        *this >>= exp - precision;
    }
    exp = precision;
}

LongNum LongNum::with_precision(const unsigned precision) const {
    if (exp < precision) {
        LongNum res = *this << (precision - exp);
        res.exp = precision;
        return res;
    }
    if (exp > precision) {
        LongNum res = *this >> (exp - precision);
        res.exp = precision;
        return res;
    }
    return *this;
}

void LongNum::remove_leading_zeros() {
    while (!chunks.empty() && chunks.back() == 0) {
        chunks.pop_back();
    }
    if (chunks.empty()) {
        sign = false;
    }
}

LongNum LongNum::truncate() const {
    return this->with_precision(0);
}

LongNum LongNum::frac() const {
    return *this - this->truncate();
}

void LongNum::shrink_to_fit() {
    chunks.shrink_to_fit();
}

LongNum LongNum::pow(unsigned power) const {
    LongNum res = 1, a = *this;
    while (power) {
        if (power & 1)
            res *= a;
        a *= a;
        power >>= 1;
    }
    return res;
}

LongNum LongNum::sqrt() const {
    if (*this < 0) {
        throw std::invalid_argument("Square root of negative number is undefined");
    }
    LongNum x0 = 0, x1 = 1;
    while (x0 != x1) {
        x0 = x1;
        x1 += *this / x1;
        x1 >>= 1;
    }
    return x1;
}

std::string LongNum::to_binary_string() const {
	if (*this == 0) {
        return "0";
    }
    std::string res;
    if (sign) {
        res = "-";
    }
    for (uint32_t limb : chunks) {
        for (unsigned j = 0; j < BASE; j++) {
            res += std::to_string((limb >> j) & 1);
        }
    }
    while (res.back() == '0' && res.length() > exp + 1) {
        res.pop_back();
    }
    if (exp > 0) {
        res.insert(res.begin() + exp, '.');
    }
    std::ranges::reverse(res);
    return res;
}

LongNum LongNum::from_binary_string(std::string str) {
    if (str.empty()) {
        throw std::invalid_argument("Invalid string");
    }
    LongNum res;
    const size_t point_pos = str.find_first_of(".,");
    if (point_pos == std::string::npos) {
        res.exp = 0;
    } else {
        res.exp = str.size() - point_pos - 1;
        str.erase(str.begin() + point_pos);
    }
    if (str.find_first_of(".,") != std::string::npos) {
        throw std::invalid_argument("Invalid string");
    }
    for (const auto c: str) {
        if (c != '0' && c != '1') {
            throw std::invalid_argument("Invalid string");
        }
    }
    for (int i = (int)str.size() - 1; i >= 0; i -= BASE) {
        res.chunks.push_back(0);
        for (unsigned j = 0; j < std::min(BASE, (unsigned)i + 1); j++) {
            if (str[i - j] == '1') {
                res.chunks.back() |= (1 << j);
            }
        }
    }
    if (res.exp < DEFAULT_PRECISION) {
        res.set_precision(DEFAULT_PRECISION);
    }
    return res;
}

std::string LongNum::to_string(unsigned decimal_precision) const {
    const LongNum base = 10;  // TODO: make it work with any base
    std::string res;
    LongNum whole = this->truncate();
    while (whole != 0) {
        LongNum q = whole / base;
        LongNum r = whole - q * base;
        if (r == 0) {
            res += '0';
        } else {
            res += std::to_string(r.chunks.front());
        }
        whole = q;
    }
    if (res.empty()) {
        res += '0';
    }
    if (sign) {
        res += '-';
    }
    std::ranges::reverse(res);
    if (decimal_precision == 0) {
        return res;
    }
    LongNum frac = this->frac();
    if (frac == 0) {
        return res;
    }
    res += '.';
    unsigned cnt = 0;
    while (frac != 0 && cnt++ < decimal_precision) {
        frac *= base;
        LongNum r = frac.truncate();
        frac -= r;
        if (r == 0) {
            res += '0';
        } else {
            res += std::to_string(r.chunks.front());
        }
    }
    return res;
}

LongNum LongNum::from_string(std::string str, const std::optional<unsigned>& precision) {
    const LongNum base = 10;  // TODO: make it work with any base
    if (str.empty()) {
        throw std::invalid_argument("Invalid string");
    }
    LongNum res = 0;
    if (str.front() == '-') {
        str.erase(str.begin());
        res.sign = true;
    }
    if (str.front() == '+') {
        str.erase(str.begin());
    }
    const size_t point_pos = str.find_first_of(".,");
    unsigned decimal_exp;
    if (point_pos == std::string::npos) {
        decimal_exp = 0;
    } else {
        decimal_exp = str.size() - point_pos - 1;
        str.erase(str.begin() + point_pos);
    }
    if (str.find_first_of(".,") != std::string::npos) {
        throw std::invalid_argument("Invalid string");
    }
    for (const auto c: str) {
        if (c < '0' || c > '9') {
            throw std::invalid_argument("Invalid string");
        }
    }
    for (const auto digit: str) {
        res *= base;
        res += digit - '0';
    }
    if (decimal_exp == 0) {
        res.set_precision(precision.value_or(0));
    } else {
        res.set_precision(precision.value_or(std::max(decimal_exp * 4, DEFAULT_PRECISION)));
    }
    res /= base.pow(decimal_exp);
    return res;
}

LongNum operator""_ln(const long double number) {
    return LongNum::from_string(std::to_string(number));
}

LongNum operator""_ln(const unsigned long long number) {
    return LongNum(number);
}

LongNum operator""_ln(const char* number, std::size_t len) {
    return LongNum::from_string(std::string(number, len));
};

std::istream& operator>>(std::istream& stream, LongNum& number) {
    std::string str;
    stream >> str;
    number = LongNum::from_string(str);
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const LongNum& number) {
    return stream << number.to_string();
}

LongNum calculate_pi(const unsigned precision) {
    LongNum k = 1;
    LongNum a_k = (1_ln).with_precision(precision);
    LongNum a_sum = (1_ln).with_precision(precision);
    LongNum b_sum = 0;

    const LongNum C = 640320;
    const LongNum C3_OVER_24 = C.pow(3) / 24;

    while (a_k != 0_ln) {
        a_k *= -(6 * k - 5) * (2 * k - 1) * (6 * k - 1);
        a_k /= k.pow(3) * C3_OVER_24;
        a_sum += a_k;
        b_sum += k * a_k;
        k += 1;
    }

    LongNum total = a_sum * 13591409 + b_sum * 545140134;
    LongNum pi = (426880 * (10005_ln).with_precision(precision).sqrt()) / total;
    
    return pi;
}
