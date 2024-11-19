#include <stdio.h>
#include <stdlib.h>

int mymin(int a, int b){
    if (a == -1){
        return b;
    }

    if (b == -1){
        return a;
    }

    if (a < b){
        return a;
    }

    return b;
}

int main(void){
    int dx[8]  = {1, 1, -1, -1, 2, 2, -2, -2};
    int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};

    int n;
    scanf("%d", &n);

    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    x1--; y1--; x2--; y2--;

    int** mat = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++){
        mat[i] = malloc(sizeof(int) * n);
        
        for (int j = 0; j < n; j++){
            mat[i][j] = -1;
        }
    }
    mat[x1][y1] = 0;

    int* qx = malloc(sizeof(int) * n*n);
    int* qy = malloc(sizeof(int) * n*n);
    for (int i = 0; i < n; i++){
        qx[i] = -1;
        qy[i] = -1;
    }

    qx[0] = x1;
    qy[0] = y1;
    int q = 1;

    for (int k = 0; k < q; k++){
        int x = qx[k];
        int y = qy[k];

        for (int i = 0; i < 8; i++){
            int x_ = x + dx[i];
            int y_ = y + dy[i];

            if ((x_ < 0) || (x_ >= n)){
                continue;
            }
            if ((y_ < 0) || (y_ >= n)){
                continue;
            }

            if (mat[x_][y_] == -1){
                mat[x_][y_] = mat[x][y] + 1;

                qx[q] = x_;
                qy[q] = y_;
                q++;
            }
        }
    }

    printf("%d\n", mat[x2][y2]);


    free(qx);
    free(qy);
    for (int i = 0; i < n; i++){
        free(mat[i]);
    }
    free(mat);

    return 0;
}   