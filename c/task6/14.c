#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 2e6 + 10;

__int16_t reverse16(__int16_t x){
    __int16_t b0 = (x & 0x00FF) << 8;
    __int16_t b1 = (x & 0xFF00) >> 8;

    return b0 | b1;
}

__int32_t reverse32(__int32_t x){
    __int32_t b0 = (x & 0x000000FF) << 24;
    __int32_t b1 = (x & 0x0000FF00) << 8;
    __int32_t b2 = (x & 0x00FF0000) >> 8;
    __int32_t b3 = (x & 0xFF000000) >> 24;

    return b0 | b1 | b2 | b3;
}

__int64_t reverse64(__int64_t x){
    __int64_t byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7;

    byte0 = (x & 0x00000000000000FF) << 56;
    byte1 = (x & 0x000000000000FF00) << 40;
    byte2 = (x & 0x0000000000FF0000) << 24;
    byte3 = (x & 0x00000000FF000000) << 8;
    byte4 = (x & 0x000000FF00000000) >> 8;
    byte5 = (x & 0x0000FF0000000000) >> 24;
    byte6 = (x & 0x00FF000000000000) >> 40;
    byte7 = (x & 0xFF00000000000000) >> 56;

    return (byte0 | byte1 | byte2 | byte3 | byte4 | byte5 | byte6 | byte7);
}

int main(void){
    FILE* in = fopen("matrix.in", "rb");

    __int16_t n = 0;

    fread(&n, 2, 1, in);
    
    printf("%u\n", n);
    n = reverse16(n);
    printf("%u\n", n);

    __int64_t res = 0;

    __int32_t x;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            fread(&x, 4, 1, in);

            if (i == j){
               res += reverse32(x); 
            }
        }
    }
    res = reverse64(res);

    fclose(in);

    FILE* out = fopen("trace.out", "wb");
    
    fwrite(&res, 8, 1, out);
    
    fclose(out);

    return 0;
}   