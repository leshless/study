#include <stdio.h>
#include <string.h>

int max(int a, int b){
    return (a > b ? a : b);
}

int max_chain(int n, char words[30][10], short used[10], char prev){
    int res = 1;

    for (int i = 0; i < n; i++){
        if (used[i]){
            continue;
        }

        if(words[i][0] != prev){
            continue;
        }

        used[i] = 1;
        res = max(res, max_chain(n, words, used, words[i][strlen(words[i]) - 1]) + 1);
        used[i] = 0;
    }

    return res;
}


int main(void){
    int n;
    scanf("%d", &n);

    char words[30][10];
    
    for (int i = 0; i < n; i++){
        scanf("%s", words[i]);
    }

    short used[10];
    int res[10];
    int mx = 0;

    for (int i = 0; i < n; i++){
        used[i] = 1;
        res[i] = max_chain(n, words, used, words[i][strlen(words[i])-1]);
        used[i] = 0;

        mx = max(mx, res[i]);
    }

    printf("%d\n", mx);

    for (int i = 0; i < n; i++){
        if (res[i] != mx){
            continue;
        }

        else {
            printf("%s\n", words[i]);
        }
    }


    return 0;
}   