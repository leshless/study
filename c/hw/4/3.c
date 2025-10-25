#include <stdio.h>
#include <string.h>

int main(void){
    char s[10010];
    scanf("%s", s);

    int n = strlen(s);

    for (int t = 1; t <= n; t++){
        short f = 1;
        for (int i = t; i < n; i++){
            if (s[i] != s[i-t]){
                f = 0;
                break;
            }
        }

        if (f){
            printf("%d ", t);
        }
    }
    printf("\n");  


    return 0;
}   