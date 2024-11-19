#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
    if (a > b){
        return a;
    }

    return b;
}

int main(void){
    int n, m;
    scanf("%d %d", &n, &m);

    int** mat = malloc(sizeof(int*) * n);

    for (int i = 0; i < n; i++){
        mat[i] = malloc(sizeof(int*) * m);

        for (int j = 0; j < m; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int** dp = malloc(sizeof(int*) * n);

    for (int i = 0; i < n; i++){
        dp[i] = malloc(sizeof(int*) * m);
        dp[i][0] = mat[i][0];
    }
    

    for (int j = 1; j < m; j++){
        for (int i = 1; i < n-1; i++){
            dp[i][j] = max(dp[i-1][j-1], max(dp[i][j-1], dp[i+1][j-1])) + mat[i][j];
        }

        dp[0][j] = max(dp[0][j-1], dp[1][j-1]) + mat[0][j];
        dp[n-1][j] = max(dp[n-1][j-1], dp[n-2][j-1]) + mat[n-1][j];
    }

    int res = 0;
    for (int i = 0; i < n; i++){
        res = max(res, dp[i][m-1]);
    }

    printf("%d\n", res);

    for (int i = 0; i < n; i++){
        free(mat[i]);
        free(dp[i]);
    }
    free(mat);
    free(dp);

    return 0;
}   