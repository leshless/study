#include <stdio.h>

short isprime(int n){
    if (n == 1){
        return 0;
    }

    for (int i = 2; i < n; i++){
        if (i*i > n){
            break;
        }

        if (n % i == 0){
            return 0;
        }   
    }

    return 1;
}

const int M = 1000000007;

int main(void){
    int n;
    scanf("%d", &n);

    for (int p = n; p <= M; p++){
        if (isprime(p)){
            printf("%d\n", p);
            return 0;
        }
    }

    return 0;
}   