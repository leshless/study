#include <stdio.h>
#include <stdlib.h>

long long trace(long long** mat, int m){
    long long res = 0;

    for (int i = 0; i < m; i++){
        res += mat[i][i];
    }

    return res;
}

int main(void){
    int n;
    scanf("%d", &n);

    long long** res = NULL;
    int k = -1;

    while (n--){
        int m;
        scanf("%d", &m);

        long long** mat = malloc(sizeof(long long*) * m);
        for (int i = 0; i < m; i++){
            mat[i] = malloc(sizeof(long long) * m);
            for (int j = 0; j < m; j++){
                scanf("%lld", &mat[i][j]);
            }
        }

        if (res == NULL || trace(res, k) < trace(mat, m)){
            for (int i = 0; i < k; i++){
                free(res[i]);
            }
            free(res);

            res = mat;
            k = m;
        }else{
            for (int i = 0; i < m; i++){
                free(mat[i]);
            }
            free(mat);
        }
    }

    for (int i = 0; i < k; i++){
        for (int j = 0; j < k; j++){
            printf("%lld ", res[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < k; i++){
        free(res[i]);
    }
    free(res);

    return 0;
}   