#include <stdio.h>

const int N = 4000;

int main(void){
    int n;
    scanf("%d", &n);
    
    int nums[N];

    for (int i = 0; i < n; i++){
        scanf("%d", &nums[i]);
    }

    int res = 0;
    for (int i = 0; i < n; i++){
        for (int j = i+2; j < n; j+=2){
            int k = (i+j)/2;

            if (nums[i] + nums[j] == 2 * nums[k]){
                res++;
            }
        }
    }

    printf("%d\n", res);

    return 0;
}   