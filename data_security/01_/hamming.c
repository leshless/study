#include <string.h>
#include <stdio.h>
#include <limits.h>

short encode_hamming(short x) {
    short r1 = ((x >> 3) & 1) ^ ((x >> 2) & 1) ^ ((x >> 1) & 1);
    short r2 = ((x >> 2) & 1) ^ ((x >> 1) & 1) ^ (x & 1);
    short r3 = ((x >> 3) & 1) ^ ((x >> 2) & 1) ^ (x & 1);

    return (x << 3) + (r1 << 2) + (r2 << 1) + r3;
}

short decode_hamming(short x) {
    short s1 = ((x >> 6) & 1) ^ ((x >> 5) & 1) ^ ((x >> 4) & 1) ^ ((x >> 2) & 1);
    short s2 = ((x >> 5) & 1) ^ ((x >> 4) & 1) ^ ((x >> 3) & 1) ^ ((x >> 1) & 1);
    short s3 = ((x >> 6) & 1) ^ ((x >> 5) & 1) ^ ((x >> 3) & 1) ^ (x & 1);

    short s = (s1 << 2) + (s2 << 1) + s3;

    x >>= 3;

    switch (s) {
    case 0b011:
        return x ^ 0b1;
    case 0b101:
        return x ^ 0b1000;
    case 0b110:
        return x ^ 0b0010;
    case 0b111:
        return x ^ 0b0100;
    }

    return x;
}

void print_binary(short num, size_t sz) {
    for (int i = sz-1; i >= 0; i--) {
        short mask = 1U << i;

        if ( (num & mask) != 0) {
            printf("1");
        } else {
            printf("0");
        }
    }
}



int main() {
    for (short x = 0; x < (1 << 4); x++) {
        print_binary(x, 4);
        printf(" -> ");
        print_binary(encode_hamming(x), 7);
        printf("\n");
    }
}