#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 210;

int max(int a, int b){
    if (a > b){
        return a;
    }

    return b;
}

int main(void){
    char* s = malloc(N);
    scanf("%s", s);

    int n = strlen(s);

    short* a = malloc(sizeof(short) * N);
    int na = 0;
    short* b = malloc(sizeof(short) * N);
    int nb = 0;
    short* c = malloc(sizeof(short) * N);
    int nc = 0;

    short step = 0;
    for (int i = n-1; i >= 0; i--){
        char x = s[i];

        if (x == '=' || x == '+'){
            step++;
            continue;
        }

        switch (step){
        case 0:
            if (x == '?'){
                c[nc] = -1;
            }else{
                c[nc] = x - '0';
            }
            nc++;
            break;

        case 1:
            if (x == '?'){
                b[nb] = -1;
            }else{
                b[nb] = x - '0';
            }
            nb++;
            break;

        case 2:
            if (x == '?'){
                a[na] = -1;
            }else{
                a[na] = x - '0';
            }
            na++;
            break;
        
        }
    }

    free(s);

    n = max(na, max(nb, nc));

    for (int i = na; i < n; i++){
        a[i] = 0;
    }
    for (int i = nb; i < n; i++){
        b[i] = 0;
    }
    for (int i = nc; i < n; i++){
        c[i] = 0;
    }

    // for (int i = 0; i < n; i++){
    //     printf("%d ", a[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < n; i++){
    //     printf("%d ", b[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < n; i++){
    //     printf("%d ", c[i]);
    // }
    // printf("\n");

    // ? + x - 1 = y

    short* need_carry = malloc(sizeof(short) * n);
    for (int i = n-1; i >= 0; i--){
        if (a[i] != -1 && b[i] != -1 && c[i] != -1){
            if (a[i] + b[i] == c[i]){
                continue;
            }
            if (a[i] + b[i] + 1 == c[i]){
                need_carry[i] = 1;
                continue;
            }

            printf("No");
            return 0;
        }else if (i != n-1 && need_carry[i+1]){

        }
    }

    return 0;
}   