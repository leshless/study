#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 2e5 + 10;

int main(void){
    FILE* in = fopen("input.txt", "r+");
    char* buf = malloc(N);

    int w = 0;
    int s = 0;
    int p = 1;
    short prev_nl = 0;

    while (fgets(buf, N, in) != NULL){
        int n = strlen(buf);

        short only_spaces = 1;
        for (int i = 0; i < n; i++){
            if (buf[i] != ' ' && buf[i] != '\n'){
                only_spaces = 0;
            }
        }

        if (only_spaces){
            prev_nl = 1;
            continue;
        }

        if (prev_nl){
            prev_nl = 0;
            p++;
        }

        for (int i = 0; i < n; i++){
            if (buf[i] == ' ' && buf[i-1] != ' '){
                w++;
            }
            if (buf[i] == '.'){
                s++;
            }
        }

        if (buf[n-2] != '-'){
            w++;
        }
    }

    fclose(in);
    free(buf);

    FILE* out = fopen("output.txt", "w+");
    fprintf(out, "%d %d %d\n", w, s, p);

    fclose(out);


    return 0;
}   