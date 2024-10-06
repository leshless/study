#include <stdio.h>

int main(void){
    int n;
    scanf("%d", &n);
    
    int seen[10001] = {0};


    for (int i = 0; i < n; i++){
        int x;
        scanf("%d", &x);

        if (x >= 1){
            seen[x]++;
        }
    }

    for (int x = 1; x <= n; x++){
        if (seen[x] != 1){
            printf("No\n");
            return 0;
        }
    }

    printf("Yes\n");

    return 0;
}   