#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n;
    scanf("%d", &n);

    char* s = malloc(n + 1);
    scanf("%s", s);

    int i = 0;
    int j = n-1;

    while (i < j){
        if (s[i] != s[j]){
            printf("NO\n");
            return 0;
        }

        i++;
        j--;
    }

    free(s);

    printf("YES\n");
    
    return 0;
}   