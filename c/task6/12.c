#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 2010;
const int M = 26;

struct trie {
    struct trie** nexts;
};

struct trie* alloc_node(){
    struct trie* node = malloc(sizeof(struct trie));
    node->nexts = malloc(M * sizeof(struct trie*));
    for (int i = 0; i < M; i++){
        node->nexts[i] = NULL;
    }

    return node;
}

void free_node(struct trie* node){
    for (int i = 0; i < M; i++){
        free(node->nexts[i]);
    }
    free(node->nexts);
}

void build(struct trie* u, int i, char* s, int n){
    if (i == n){
        return;
    }

    int x = s[i] - 'a';
    struct trie* v = u->nexts[x];

    if (v == NULL) {
        v = alloc_node();
        u->nexts[x] = v;
    }

    build(v, i+1, s, n);
}

int count(struct trie* u){
    if (u == NULL){
        return 0;
    }

    int res = 1;

    for (int j = 0; j < M; j++){
        res += count(u->nexts[j]);
    }

    return res;
}

void destroy(struct trie* u){
    for (int j = 0; j < M; j++){
        struct trie* v = u->nexts[j];

        if (v != NULL){
            destroy(v);
            free_node(v);
        }
    }
}

int main(void){
    char* s = malloc(sizeof(char) *N);
    scanf("%s", s);
    int n = strlen(s);

    struct trie* head = alloc_node();
    for (int i = 0; i < n; i++){
        build(head, i, s, n);
    }

    int res = count(head);
    printf("%d\n", res);

    free(s);
    destroy(head);
    free_node(head);

    return 0;
}