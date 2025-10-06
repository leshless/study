#include <stdio.h>

int main(void){
    int n;
    scanf("%d", &n);

    int a[10000];
    int b[10000];

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    long long res = 0;

    for (int i = 0; i < n; i++) {
        res += (a[i] > b[i] ? a[i] : b[i]);
    }

    printf("%lld\n", res);

    return 0;
}   