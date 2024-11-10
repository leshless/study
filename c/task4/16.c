#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int N = 2000001;

int main(void){
    char s[N];
    scanf("%s", s);

    int n = strlen(s);

    int j = 0;

    for (int i = 0; i < n; i++){
        if (s[i] == '0'){
            for (int k = 0; k < n; k++){
                if (s[(i + k) % n] > s[(j + k) % n]){
                    break;
                }
                if (s[(i + k) % n] < s[(j + k) % n]){
                    j = i;
                    break;
                }
            }
        }
    }

    for (int k = 0; k < n; k++){
        printf("%c", s[(j + k) % n]);
    }
    printf("\n");

    return 0;
}