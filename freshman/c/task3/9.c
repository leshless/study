#include <stdio.h>
#include <math.h>

struct point {
    double x;
    double y;
};
typedef struct point point;


double dst(point a, point b){
    double dx = b.x - a.x;
    double dy = b.y - a.y;

    return sqrt(dx*dx + dy*dy);
}

point vec(point a, point b){
    point v = {b.x - a.x, b.y - a.y};
    return v;
}

point scale(point v, double r){
    point vr = {v.x * r, v.y * r};
    return vr;
}

void print_bisect_point(point a, point b, point c) {
    double bc = dst(b, c);
    double ac = dst(a, c);
    double r = ac / (ac + bc);

    point v = vec(a, b);
    v = scale(v, r);

    point res = {a.x + v.x, a.y + v.y};
    printf("%.5lf %.5lf\n", res.x, res.y);

    return;
}

int main(void){
    point a, b, c;
    scanf("%lf %lf\n%lf %lf\n%lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);

    print_bisect_point(a, b, c);
    print_bisect_point(b, c, a);
    print_bisect_point(c, a, b);
    
    return 0;
}   