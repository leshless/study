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

        default:
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

    // 3 + 1 = 4 <- need_carry
    // 2 + ? = 2 <- need_carry

    short* need_carry = malloc(sizeof(short) * (n + 1));
    need_carry[n] = -1; // the radix of number n+1 strictly doesn't need carry
    
    for (int i = n-1; i >= 0; i--){
        short carry_next = need_carry[i+1];

        short can_carry = 0;
        short can_no_carry = 0;

        for (short j = 0; j < 10; j++){
            short ad = (a[i] == -1 ? j : a[i]);
            
            for (short k = 0; k < 10; k++){
                short bd = (b[i] == -1 ? k : b[i]);
                
                for (short l = 0; l < 10; l++){
                    short cd = (c[i] == -1 ? l : c[i]);

                    int s0 = ad + bd;
                    if (s0 % 10 == cd){
                        if (carry_next == 0 || ((carry_next == -1) && (s0 < 10)) || ((carry_next == 1) && (s0 >= 10))){
                            can_no_carry = 1;
                        }
                    }

                    int s1 = ad + bd + 1;
                    if (s1 % 10 == cd){
                        if (carry_next == 0 || ((carry_next == -1) && (s1 < 10)) || ((carry_next == 1) && (s1 >= 10))){
                            can_carry = 1;
                        }
                    }
                }
            }
        }

        if (can_carry){
            if (can_no_carry){
                need_carry[i] = 0;
            }else{
                need_carry[i] = 1;
            }
        }else{
            if (can_no_carry){
                need_carry[i] = -1;
            }else{
                printf("No");
                return 0;
            }
        }

    }

    // for (int i = 0; i < n; i++){
    //     printf("%d ", need_carry[i]);
    // }
    // printf("\n");

    need_carry[n] = -1;

    if (need_carry[0] == 1){
        printf("No\n");
        return 0;
    }

    int carry = 0;

    for (int i = 0; i < n; i++){
        short f = 0;
        for (short j = 0; j < 10; j++){
            short ad = (a[i] == -1 ? j : a[i]);
            
            for (short k = 0; k < 10; k++){
                short bd = (b[i] == -1 ? k : b[i]);
                
                for (short l = 0; l < 10; l++){
                    short cd = (c[i] == -1 ? l : c[i]);

                    int s = ad + bd + carry;

                    if (s % 10 == cd){
                        if ((need_carry[i+1] == 1 && s < 10)){
                            continue;
                        }else if (need_carry[i+1] == -1 && s >= 10){
                            continue;
                        }

                        a[i] = ad;
                        b[i] = bd;
                        c[i] = cd;

                        f = 1;
                        carry = (s >= 10);
                    }

                    if (f){
                        goto found;
                    }
                }
            }
        }

        found:
        if (!f){
            printf("No\n");
            return 0;
        }
    }

    for (int i = na-1; i >= 0; i--){
        printf("%c", '0' + a[i]);
    }
    printf("+");
    for (int i = nb-1; i >= 0; i--){
        printf("%c", '0' + b[i]);
    }
    printf("=");
    for (int i = nc-1; i >= 0; i--){
        printf("%c", '0' + c[i]);
    }
    printf("\n");


    free(need_carry);
    free(a);
    free(b);
    free(c);

    return 0;
}   