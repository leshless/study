#include <stdio.h>

int main(void){
    int nums[10000];

    int n = 0;
    while (1){
        int x;
        scanf("%d", &x);

        if (x == 0){
            break;
        }
        
        nums[n] = x;
        n++;
    }

    for (int i = 0; i < n; i += 2){
        printf("%d ", nums[i]);
    }

    for (int i = ((n-1) % 2 == 1 ? n-1 : n-2); i >= 0; i -= 2){
        printf("%d ", nums[i]);
    }

    printf("\n");

    return 0;
}   