#include <stdio.h>
#include <stdlib.h>

int rc(int x){
    int res = 0;
    while (x > 0){
        res++;
        x /= 10;
    }

    return res;
}

short is_prime(int x){
    int i = 2;
    while (1){
        if (i*i > x){
            break;
        }

        if (x % i == 0){
            return 0;
        }

        i++;
    }

    return 1;
}

int main(void){
    int n;
    scanf("%d", &n);

    int* nums = malloc(sizeof(int) * 1e4);
    nums[0] = 2;
    nums[1] = 3;
    nums[2] = 5;
    nums[3] = 7;
    int m = 4;

    for (int r = 2; r <= n; r++){
        for (int j = 0; j < m; j++){
            int x = nums[j];
            if (rc(x) == r-1){
                for (int d = 0; d < 10; d++){
                    int y = 10*x + d;
                    
                    if (is_prime(y)){
                        nums[m] = y;
                        m++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < m; i++){
        if (rc(nums[i]) == n){
            printf("%d ", nums[i]);
        }
    }
    printf("\n");

    free(nums);


    return 0;
}   