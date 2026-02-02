#include <stdio.h>
#include <inttypes.h>

int main(void){
    int mx1 = INT32_MIN;
    int mx2 = INT32_MIN;
    int mx3 = INT32_MIN;

    int n;
    scanf("%d", &n);

    while (n--){
        int x;
        scanf("%d", &x);

        if (x > mx1){
            int t = mx1;
            mx1 = x;
            x = t;
        }

        if (x > mx2){
            int t = mx2;
            mx2 = x;
            x = t;
        }

        if (x > mx3){
            int t = mx3;
            mx3 = x;
            x = t;
        }

    }

    printf("%d %d %d\n", mx1, mx2, mx3);

    return 0;
}