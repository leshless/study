#include <stdio.h>
#include <math.h>

const int N = 4000;

int main(void){
    int n;
    scanf("%d", &n);
    
    double s[N];
    for (int i = 0; i < n; i++){
        scanf("%lf", &s[i]);
    }

    double a[N];
    for (int i = 0; i < n; i++){
        scanf("%lf", &a[i]);
    }

    double v0 = 0;
    double t = 0;

    for (int i = 0; i < n; i++){
        double v = sqrt(2*a[i]*s[i] + v0*v0);
        double dt = (v - v0) / a[i];

        t += dt;
        v0 = v;
    }

    printf("%.4f\n", t);
    

    return 0;
}   