#include <stdio.h>
#include <string.h>

const int N = 1000010;

void print_formated(char* s, int k){
    int n = strlen(s);
    
    if (n >= k){
        printf("%s\n", s);
        return;
    }

    int c = 0;
    for (int i = 0; i < n; i++){
        c += (s[i] == ' ');
    }

    int q = (k + c - n) / c;
    int r = (k + c - n) % c;

    c = 0;
    char res[N];
    res[0] = 0;

    for (int i = 0; i < n; i++){
        if (s[i] != ' '){
            int m = strlen(res);
            res[m] = s[i];
            res[m + 1] = 0;
            continue;
        }
        
        int m = q + (c < r);
        for (int j = 0; j < m; j++){
            strcat(res, " ");
        }

        c++;
    }

    printf("%s\n", res);
    return;
}

int main(void){
    int k;
    scanf("%d", &k);

    char cur[N];
    cur[0] = 0;
    int c = 0;

    char s[N];
    while (scanf("%s", s) != EOF){
        if (strlen(cur) + strlen(s) + 1 > k){
            if ((c == 1) && (strlen(s) != k)){
                strcat(cur, " ");
            }
            print_formated(cur, k);
            cur[0] = 0;
            c = 0;
        }

        if (c != 0){
            strcat(cur, " ");
        }
        strcat(cur, s);
        c++;
    }

    if (c == 1){
        strcat(cur, " ");
    }
    print_formated(cur, k);

    return 0;
}   //