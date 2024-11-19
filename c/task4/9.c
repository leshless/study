#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int N = 1000010;

void print_formated(char* s, int k){
    s[k] = 0;
    int n = strlen(s);
    
    if (n == k){
        printf("%s\n", s);
        return;
    }

    int c = 0;
    for (int i = 0; i < n; i++){
        c += (s[i] == ' ');
    }

    if ((c != 1) && (s[n-1] == ' ')){
        s[n-1] = 0;
        n -= 1;
        c -= 1;
    }

    if (c == 0){
        printf("%s\n", s);
        return;
    }

    int q = (k + c - n) / c;
    int r = (k + c - n) % c;

    c = 0;
    char* res = malloc(N);

    int m = 0;

    for (int i = 0; i < n; i++){
        if (s[i] != ' '){
            res[m] = s[i];
            m++;

            continue;
        }
        
        int t = q + (c < r);
        for (int j = 0; j < t; j++){
            res[m] = ' ';
            m++;
        }

        c++;
    }

    res[m] = 0;
    printf("%s\n", res);
    free(res);

    return;
}

int main(void){
    int k;
    scanf("%d\n", &k);

    char* s = malloc(N);
    fgets(s, N, stdin);
    
    int n = strlen(s);
    s[n-1] = 0;
    n -= 1;

    char* cur = malloc(N);
    int m = 0;

    char* word = malloc(N);
    int w = 0;

    for (int i = 0; i <= n; i++){
        if ((i < n) && (s[i] != ' ')){
            word[w] = s[i];
            word[w+1] = 0;
            w++;

            continue;
        }

        if (w + m > k){
            print_formated(cur, k);
            
            strcpy(&cur[0], word);
            m = w;
        }else{
            strcpy(&cur[m], word);
            m += w;
        }
       
        word[0] = 0;
        w = 0;
    
        if (m != k){
            cur[m] = ' ';
            cur[m+1] = 0;
            m += 1;
        }    
    }

    print_formated(cur, k);

    free(word);
    free(cur);
    free(s);

    return 0;
}
