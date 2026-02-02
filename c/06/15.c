#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 110;
const int M = 30;

struct trie {
    long long x;
    struct trie **nexts;
};

int map(char x){
    if (('a' <= x) && (x <= 'z')){
        return x - 'a';
    }
    if (x == '.'){
        return 26;
    }

    return 27;
}

void add(struct trie* u, long long x, char* s, int i, int n){
    if (i == n){
        u->x = x;
        return;
    }

    int j = map(s[i]);
    struct trie* v = u->nexts[j];

    if (v == NULL) {
        v = malloc(sizeof(struct trie));
        v->x = -1;
        v->nexts = malloc(M * sizeof(struct trie*));
        for (int k = 0; k < M; k++){
            v->nexts[k] = NULL;
        }

        u->nexts[j] = v;
    }


    add(v, x, s, i+1, n);
}

long long get(struct trie* u, char* s, int i, int n){
    if (u == NULL){
        return -1;
    }
    if (i == n){
        return u->x;
    }

    int j = map(s[i]);
    struct trie* v = u->nexts[j];

    return get(v, s, i+1, n);
}

void destroy(struct trie* u){
    for (int j = 0; j < M; j++){
        struct trie* v = u->nexts[j];

        if (v != NULL){
            destroy(v);
            free(v);
        }
    }

    free(u->nexts);
}


int main(void){
    FILE* in = fopen("input.txt", "r+");
    FILE* out = fopen("output.txt", "w+");

    int m;
    fscanf(in, "%d", &m);

    struct trie* head = malloc(sizeof(struct trie));
    head->x = -1;
    head->nexts = malloc(M * sizeof(struct trie*));
    for (int i = 0; i < M; i++){
        head->nexts[i] = NULL;
    }


    char* s = malloc(N);
    long long x;
    while (m--){
        fscanf(in, "%s %lld", s, &x);
        add(head, x, s, 0, strlen(s));
    }

    int q;
    fscanf(in, "%d", &q);

    while (q--){
        fscanf(in, "%s", s);
        x = get(head, s, 0, strlen(s));
        fprintf(out, "%lld\n", x);
    }

    destroy(head);
    free(head);
    free(s);


    fclose(in);
    fclose(out);

    return 0;
}   