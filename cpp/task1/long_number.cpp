#include <bits/stdc++.h>

const size_t INIT_PRECISION = 16;
const size_t INIT_LENGTH = 4;

class long_number {
// Internal fields
private:
    std::vector<uint8_t> bytes;
    size_t precision;
    uint8_t sign;

// Helper functions
private:
    void resize(size_t new_size) {
        size_t size = this->bytes.size();

        if (size == new_size) {
            return;
        }else if (size > new_size) {
            throw "TODO: exception";
        }
        
        this->bytes.resize(new_size);
    }

    void lshift(size_t offset) {
        size_t size = this->bytes.size();
        size_t q = offset / 8;
        size_t r = offset % 8;

        // Resize here to make sure that we won't overflow
        size_t new_size = size + q + (r == 0 ? 0 : 1);
        this->resize(new_size);
    
        for (int i = new_size - 1; i >= 0; --i){
            // Two adjacent bytes, whe are interested in
            uint8_t lb = (i - q >= 0 ? this->bytes[i - q] : 0);
            uint8_t rb = (i - q - 1 >= 0 ? this->bytes[i - q - 1] : 0);

            //         V                 V
            // |xxxxxxxx|xxxxxxxx|xxxxxxxx|
            this->bytes[i] = (lb << r) | (rb >> (8 - r));
        }   
    }

    void rshift(size_t offset) {
        size_t size = this->bytes.size();
        size_t q = offset / 8;
        size_t r = offset % 8;
    
        for (int i = 0; i < size; ++i){
            // Two adjacent bytes, whe are interested in
            uint8_t rb = (i + q < size ? this->bytes[i + q] : 0);
            uint8_t lb = (i + q + 1 < size ? this->bytes[i + q + 1] : 0);

            //         V           V
            // |xxxxxxxx|xxxxxxxx|xxxxxxxx|
            this->bytes[i] = (lb << (8 - r)) | (rb >> r);
        }  
    }

// Public functions
public:
    void set_precision(size_t new_precision){
        size_t precision = this->precision;

        size_t offset;
        if (new_precision > precision) {
            offset = new_precision - precision;
            this->lshift(offset);
        }else{
            offset = precision - new_precision;
            this->rshift(offset);
        }

        this->precision = new_precision;
    }

    std::string binary_string(){
        size_t size = this->bytes.size();
        size_t precision = this->precision;

        std::string res;

        for (int i = 0; i < size; i++){
            for (int j = 0; j < 8; j++){
                if (i * 8 + j == precision){
                    res.push_back('.');
                }

                uint8_t b = this->bytes[i] & (1 << j);
                res.push_back(b == 0 ? '0' : '1');
            }
        }

        std::reverse(res.begin(), res.end());
        return res;
    }

// Operations
public:
    long_number& operator=(const long_number& other){
        if (this == &other){
            return *this;
        }
    
        std::copy(other.bytes.begin(), other.bytes.end(), this->bytes);
        this->precision = other.precision;
        this->sign = other.sign;

        return *this;
    }


    long_number& operator+(const long_number& other){
        long_number res = *this;

        res.set_precision(std::max(this->precision, other.precision));
        res.resize(std::max(this->bytes.size(), other.bytes.size()) + 1);


    }

// Constructors
public:
    long_number() {
        this->bytes = std::vector<uint8_t>(INIT_LENGTH, 0);
        this->precision = INIT_PRECISION;
        this->sign = 0;
    }

    long_number(uint8_t a){
        this->bytes = std::vector<uint8_t>(INIT_LENGTH, 0);
        this->bytes[0] = a;
        this->precision = INIT_PRECISION;
        this->sign = 0;
    }

    ~long_number() {
        // No mallocs of fields here, so just empty destructor
    }
};

int main() {
    long_number x = long_number(10);
    std::cout << x.binary_string() << std::endl;

    x.set_precision(30);
    std::cout << x.binary_string() << std::endl;
}