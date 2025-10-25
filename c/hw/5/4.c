#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n = 5;
    int i = 0;

    int* nums = malloc(sizeof(int) * n);

    while (1) {
        int x;
        scanf("%d", &x);
        
        if (x == 0){
            break;
        }

        nums[i] = x;
        i++;

        if (i == n){
            n *= 2;
            nums = realloc(nums, sizeof(int) * n);
        }
    }

    n = i;

    int res = 0;
    for (i = 0; i < n; i++){
        res += (nums[i] < nums[n-1]);
    }

    free(nums);

    printf("%d\n", res);
    

    return 0;
}   