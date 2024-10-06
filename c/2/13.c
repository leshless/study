#include <stdio.h>

int main(void){
    int a[8];
    for (int i = 0; i < 8; i++){
        scanf("%d", &a[i]);
    }

    int b[8];
    for (int i = 0; i < 8; i++){
        scanf("%d", &b[i]);
    }

    int af[8] = {0};
    int bf[8] = {0};

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (!af[i] && !bf[j] && (a[i] == b[j])){
                af[i] = 1;
                bf[j] = 1;
            } 
        }
    }


    int once = 0;
    int twice = 0;

    for (int i = 0; i < 8; i++){
        if (af[i]){
            twice += a[i];
        }else{
            int ok = 0;
            for (int j = 0; j < 8; j++){
                ok |= a[i] <= b[j];
            }

            if (ok){
                once += a[i];
            }else{
                printf("-1\n");
                return 0;
            }
        }
    }

    for (int j = 0; j < 8; j++){
        if (bf[j]){
            twice += b[j];
        }else{
            int ok = 0;
            for (int i = 0; i < 8; i++){
                ok |= b[j] <= a[i];
            }

            if (ok){
                once += b[j];
            }else{
                printf("-1\n");
                return 0;
            }
        }
    }

    int res = once + twice / 2;
    printf("%d\n", res);

    return 0;
}   