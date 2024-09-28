#include <stdio.h>
#include <inttypes.h>

int main(void){
    unsigned x;
    scanf("%u", &x);

    int cnt = 0;
    for (int i = 0; i < 32; i++){
        cnt += (x >> i) & 1;
    }

    printf("%d\n", cnt);

    return 0;
}