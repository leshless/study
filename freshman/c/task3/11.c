#include <stdio.h>

int gcd(int a, int b){
    if (b == 0){
        return a;
    }

    return gcd(b, a%b);
}

int main(void){
    int n;
    scanf("%d", &n);

    int y = 0;
    int z = 1;

    for(int i = 0; i < n; i++){
        int a, b;
        scanf("%d %d", &a, &b);

        y = y*b + z*a;
        z = z*b;

        int g = gcd(y, z);
        y /= g;
        z /= g;
    }

    int x = y / z;
    y = y % z;

    printf("%d %d %d\n", x, y, z);
    
    return 0;
}   