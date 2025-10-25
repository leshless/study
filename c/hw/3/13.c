#include <stdio.h>

void print_seq(int k, int seq[]){
    for (int i = 0; i < k; i++){
        printf("%d ", seq[i]);
    }
    printf("\n");
}

void print_all_seqs(int i, int d, int n, int k, int seq[]){
    int m = (i == 0 ? 0 : seq[i-1]+1);

    for (int x = m; x <= n-d; x++){
        seq[i] = x;

        if (d == 1){
            print_seq(k, seq);
        }else{
            print_all_seqs(i+1, d-1, n, k, seq);
        }
    }
}

int main(void){
    int n, k;
    scanf("%d %d", &n, &k);

    int seq[k];

    print_all_seqs(0, k, n, k, seq);

    return 0;
}   