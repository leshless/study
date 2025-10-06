#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 2e4 + 10;

short is_delim(char x){
    return (x == ' ') || (x == '\n') || (x == '.');
}

short is_letter(char x){
    return (('a' <= x) && (x <= 'z')) || (('A' <= x) && (x <= 'Z'));
}

int main(void){
    FILE* in = fopen("input.txt", "r+");
    char* buf = malloc(N);

    short prev_empty = 1;
    int w = 0;
    int s = 0;
    int p = 0;

    while (fgets(buf, N, in) != NULL){
        int n = strlen(buf);
        char cur_empty = 1;

        for (int i = 0; i < n; i++){
            if ((i != 0) && is_delim(buf[i]) && is_letter(buf[i-1])){
                w++;
            }
            if (buf[i] == '.'){
                s++;
            }
            if (is_letter(buf[i])){
                cur_empty = 0;
            }
        }

        if (prev_empty && !cur_empty){
            p++;
        }

        prev_empty = cur_empty;
    }

    FILE* out = fopen("output.txt", "w+");
    fprintf(out, "%d %d %d\n", w, s, p);

    free(buf);
    fclose(in);
    fclose(out);


    return 0;
}   
