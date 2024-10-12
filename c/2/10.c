#include <stdio.h>
#include <math.h>

const int N = 100;
const double EPS = 0.000000001;

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

    double v = 0;
    double t = 0;

    for (int i = 0; i < n; i++){
        double dv = sqrt(2*a[i]*s[i] + v*v) - v;
        
        double dt;
        if ((a[i] < EPS) && (a[i] > -EPS)){
            dt = s[i]/v;
        }else{
            dt = dv/a[i];
        }

        t += dt;
        v += dv;
    }

    printf("%.4f\n", t);
    

    return 0;
}   