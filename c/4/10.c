#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int N = 2000001;

int pref(char s[N]){
    int n = strlen(s);
    
    int* p = malloc(sizeof(int) * N);
    for (int i = 0; i < n; i++){
        p[i] = 0;
    }

    for (int i = 1; i < n; i++){
        int cur = p[i-1];
        while ((s[i] != s[cur]) && (cur > 0)){
            cur = p[cur - 1];
        }

        if (s[i] == s[cur]){
            p[i] = cur + 1;
        }
    }

    return p[n-1];
}

int main(void){
    char a[N];
    scanf("%s", a);

    char b[N];
    scanf("%s", b);


    char first[N];
    strcpy(first, a);
    strcat(first, " ");
    strcat(first, b);
    
    printf("%d ", pref(first));

    char second[N];
    strcpy(second, b);
    strcat(second, " ");
    strcat(second, a);

    printf("%d\n", pref(second));


    return 0;
}