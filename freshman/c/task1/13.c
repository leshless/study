#include <stdio.h>

int main(void){
    double x;
    int n;
    scanf("%lf %d", &x, &n);

    double res = 0;
    double cur = x;

    for (int i = 0; i < n; i++){
        if (i % 2 == 0){
            res += cur;
        }else{
            res -= cur;
        }

        cur *= x*x;
        cur /= (i*2+2) * (i*2+3);
    }

    printf("%.6lf\n", res);

    return 0;
}