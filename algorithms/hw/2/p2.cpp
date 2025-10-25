#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

const int THRESHOLD = 32;

std::string add(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0;
    int i = 0;
    int j = 0;
    
    while (i < a.size() || j < b.size() || carry > 0) {
        int sum = carry;
        if (i < a.size()) {
            sum += a[i] - '0';
            i++;
        }
        if (j < b.size()) {
            sum += b[j] - '0';
            j++;
        }
        
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }

    return result;
}

std::string sub(const std::string& a, const std::string& b) {
    std::string result;
    int borrow = 0;
    int i = 0;
    int j = 0;
    
    while (i < a.size()) {
        int digitA = a[i] - '0' - borrow;
        int digitB = j < b.size() ? b[j] - '0' : 0;
        
        if (digitA < digitB) {
            digitA += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.push_back((digitA - digitB) + '0');
        i++;
        j++;
    }
    
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }
    
    return result;
}

std::string mul(const std::string& a, const std::string& b) {
    std::string result;
    std::string shift;

    for (int i = 0; i < a.size(); i++) {
        std::string cur;
        
        int j = 0;
        int carry = 0;
        for (int j = 0; j < b.size(); j++) {
            int sum = carry;
            sum += (b[j] - '0') * (a[i] - '0');
            
            cur.push_back((sum % 10) + '0');
            carry = sum / 10;
        }

        if (carry != 0) {
            cur.push_back(carry + '0');
        }
    
        cur = shift + cur;
        shift += "0";
        result = add(result, cur);  
    }
    
    return result;
}

std::string karatsuba(std::string& s1, std::string& s2) {
    int n = std::max(s1.size(), s2.size());
    if (n % 2 != 0) {
        n++;
    }

    int half = n / 2;
    
    while (s1.size() < n) {
        s1.push_back('0');
    }
    while (s2.size() < n) {
        s2.push_back('0');
    }

    if (s1.size() <= THRESHOLD && s2.size() <= THRESHOLD) {
        return mul(s1, s2);
    }
    
    std::string high1 = s1.substr(half);  // a
    std::string low1 = s1.substr(0, half); // b
    
    std::string high2 = s2.substr(half);  // c  
    std::string low2 = s2.substr(0, half); // d
    
    std::string c0 = karatsuba(low1, low2);                    // low1 * low2
    std::string c2 = karatsuba(high1, high2);                  // high1 * high2
    
    std::string sum1 = add(low1, high1);                // low1 + high1
    std::string sum2 = add(low2, high2);                // low2 + high2
    std::string product_sum = karatsuba(sum1, sum2);           // (low1+high1)*(low2+high2)
    
    std::string c1 = sub(sub(product_sum, c0), c2);
    
    std::string result = c0;
    
    std::string c1s = c1;
    std::reverse(c1s.begin(), c1s.end());
    for (int i = 0; i < half; i++) {
        c1s += "0";  
    }
    std::reverse(c1s.begin(), c1s.end());

    result = add(result, c1s);
    
    
    std::string c2s = c2;
    std::reverse(c2s.begin(), c2s.end());
    for (int i = 0; i < n; i++) {
        c2s += "0";  
    }
    std::reverse(c2s.begin(), c2s.end());

    result = add(result, c2s);
    
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s1, s2;
    std::cin >> s1 >> s2;
    
    std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());

    std::string res = karatsuba(s1, s2);
    
    while (res.size() > 1 && res.back() == '0') {
        res.pop_back();
    }
    
    std::reverse(res.begin(), res.end());
    std::cout << res << std::endl;

    return 0;
}