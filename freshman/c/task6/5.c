#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 2e6 + 10;

int main(void){
    FILE* in = fopen("input.txt", "r+");
    char* s = malloc(N);
    fgets(s, N, in);
    fclose(in);

    int n = strlen(s);
    short sgn = 1;
    long long res = 0;
    long long cur = 0;

    for (int i = 0; i < n; i++){
        char x = s[i];

        if ((x >= '0') && (x <= '9')){
            cur *= 10;
            cur += (x - '0');
        }else {
            res += cur * sgn;
            cur = 0;

            if ((i != 0) &&(s[i-1] >= '0') && (s[i-1] <= '9')){
                sgn = 1;
            }

            if (x == '-'){
                sgn = -sgn;
            }            
        }
    }
    res += cur * sgn;

    free(s);

    FILE* out = fopen("output.txt", "w+");
    fprintf(out, "%lld", res);
    fclose(out);


    return 0;
}   