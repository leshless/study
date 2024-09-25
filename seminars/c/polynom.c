#include <stdio.h>
#include <math.h>

int main(void){
    int a, b, c, d;

    if (scanf("%d %d %d", &a, &b, &c) != 3){
        printf("Input three cooficients\n");
        return 1;
    }

    if (!a){
        printf("Not a quadratic polynom\n");
        return 1;
    }

    d = b*b - 4*a*c;
    if (d < 0){
        printf("No solutions\n");
    }else if (d == 0){
        double nb = -b;
        printf("x = %.4f\n", nb/(2*a));
    }else{
        double nb = -b;
        double sr = sqrt(d);

        printf("x1 = %.4f; x2 = %.4f\n", (nb+sr)/(2*a), (nb-sr)/(2*a));
    }

    return 0;
}