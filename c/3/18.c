#include <stdio.h>

long concat(long x){
    long d = 1;
    while (d <= x){
        d *= 10;
    }

    return (x * d + x) % 2010;
}

int main(void){
    long n, a;
    scanf("%ld %ld", &n, &a);

    n %= 2010;

    short seen[2010] = {0};
    seen[n] = 1;

    if (n == a){
        printf("YES\n");
        return 0;
    }

    while (1) {
        n = concat(n);

        if (n == a){
            printf("YES\n");
            return 0;
        }            
        if (seen[n] == 1){
            printf("NO\n");
            return 0;
        }

        seen[n] = 1; 
    }

    return 0;
}       