#include <stdio.h>

int main(void){
    double x1, y1, x2, y2, x3, y3;
    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);

    double xv1 = x2 - x1;
    double yv1 = y2 - y1;

    double xm = x1 + xv1 / 2;
    double ym = y1 + yv1 / 2;

    double xv2 = x3 - xm;
    double yv2 = y3 - ym;

    double rx = xm + xv2 / 3;
    double ry = ym + yv2 / 3;

    printf("%.4lf %.4lf\n", rx, ry);

    return 0;
}