#include <stdio.h>

void foo(void){
    int x;
    scanf("%d", &x);

    if (x == 0){
        return;
    }

    foo();

    printf("%d ", x);
}

int main(void){

    foo();
    printf("\n");

    return 0;
}   