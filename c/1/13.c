#include <stdio.h>
#include <inttypes.h>

double power(double x, int n){
    if (n == 0){
        return 1;
    }
    return x * power(x, n-1);
}

double fact(int n){
    if (n == 0){
        return 1;
    }

    return n * fact(n-1);
}

int main(void){
    double x;
    int n;
    scanf("%lf %d", &x, &n);

    double res = 0;
    for (int i = 0; i < n; i++){
        int m = i*2+1;
        res += power(-1, i) * power(x, m) / fact(m);    
    }

    printf("%.6lf\n", res);

    return 0;
}