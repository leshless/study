#include <stdio.h>

long min(long a, long b){
    if (a < b){
        return a;
    }
    return b;
}

long lighten(long n){
    long j = -1;

    long back = 0;
    long forw = 0;

    long res = 0;

    for (long i = 0; i < n; i++){
        long x;
        scanf("%ld", &x);

        if (x != 0) { 
            short cur = i;
            if (forw > 0){
                cur = -1;
                res++;
            }

            if (x > 0){
                forw = x;
                back = 0;
            }else{
                x = -x;

                res += min(x, back);
                if ((j != -1) && (i - x <= j)){
                    res++;
                }

                forw = 0;
                back = 0;
            }

            j = cur;
        } else{
            if (forw > 0){
                forw--;
                res += 1;
            }else{
                back++;
            }
        }
    }

    return res;
}

int main(void){
    long n;
    scanf("%ld", &n);

    long res = lighten(n);

    printf("%ld\n", res);

    return 0;
}       