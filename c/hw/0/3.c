#include <stdio.h>

int main(void){
    int n;
    scanf("%d", &n);

    int s = n * (n+1) / 2;

    printf("%d\n", s*s);

    return 0;
}