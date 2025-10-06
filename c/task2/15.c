#include <stdio.h>

const int N = 1500000;

int main(void){
    int n;
    scanf("%d", &n);
    
    unsigned nums[N];
    for (int i = 0; i < n; i++){
        scanf("%u", &nums[i]);
    }

    unsigned x = 0;
    for (int i = 0; i < n; i++){
        x ^= nums[i];
    }    

    int j = 0;
    for (int i = 0; i < 32; i++){
        if ((x >> i) & 1){
            j = i;
            break;
        }
    }

    unsigned a = 0;
    unsigned b = 0;
    for (int i = 0; i < n; i++){
        if ((nums[i] >> j) & 1){
            a ^= nums[i];
        }else{
            b ^= nums[i];
        }
    }

    if (a > b){
        unsigned t = a;
        a = b;
        b = t;
    }

    printf("%u %u\n", a, b);
    

    return 0;
}   