#include <stdio.h>

int main(void){
    int sum = 0;
    int prod = 1;
    int cnt = 0;

    while (1){
        int x;
        scanf("%d", &x);

        if (x == 0){
            if (cnt % 2 == 0){
                sum += prod;
            }
            break;
        }

        if (cnt % 2 == 0){
            sum += prod * x;
            prod = 1;
        }else{
            prod = x;
        }

        cnt++;
    }

    printf("%d\n", sum);

    return 0;
}