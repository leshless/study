#include <stdio.h>

int func(int a, int x, int b, int y, int c){
    return ((a & x) ^ (b & y)) == c;
}

int main(void){
    // (a & x) ^ (b & y) = c
    // (d & x) ^ (e & y) = f

    unsigned a, b, c, d, e, f;
    scanf("%u %u %u %u %u %u", &a, &b, &d, &e, &c, &f);

    unsigned x = 0;
    unsigned y = 0;

    for (int i = 0; i < 32; i++){
        int ai = (a >> i) & 1;
        int bi = (b >> i) & 1;
        int ci = (c >> i) & 1;
        int di = (d >> i) & 1;
        int ei = (e >> i) & 1;
        int fi = (f >> i) & 1;

        int found = 0;
        for (int xi = 0; xi <= 1; xi++){
            if (found){
                break;
            }
            for (int yi = 0; yi <= 1; yi++){
                if (found){
                    break;
                }
                if (func(ai, xi, bi, yi, ci) && func(di, xi, ei, yi, fi)){
                    x += (xi << i);
                    y += (yi << i);

                    found = 1;
                }
            }
        }

        if (!found){
            printf("No\n");
            return 0;
        }
    }

    printf("Yes\n%u %u\n", x, y);

    return 0;
}