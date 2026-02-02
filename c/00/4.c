#include <stdio.h>

int main(void){
    int n;
    scanf("%d", &n);

    int nums[n];

    for (int i = 0; i < n; i++){
        int x;
        scanf("%d", &x);

        nums[i] = x;
    }

    int mn = nums[0];
    int mni = 0;

    int mx = nums[0];
    int mxi = 0;

    for (int i = 0; i < n; i++){
        if (nums[i] > mx){
            mx = nums[i];
            mxi = i;
        }
        if (nums[i] < mn){
            mn = nums[i];
            mni = i;
        }
    }

    int i = (mni < mxi ? mni : mxi);
    int j = (mni > mxi ? mni : mxi);

    while (i < j){
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;

        i++;
        j--;
    }

    for (int i = 0; i < n; i++){
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}