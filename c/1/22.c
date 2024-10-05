#include <stdio.h>

int abs(int n){
    return (n < 0) ? -n : n;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int min(int a, int b){
    return (a < b) ? a : b;
}

int main(void){
    int x, y;
    scanf("%d %d", &x, &y);

    x = abs(x);
    y = abs(y);

    int m = max(x, y) - min(x, y);
    int r = min(x, y) * 2 + m / 2 * 4 + (m % 2);

    printf("%d\n", r);

    return 0;
}