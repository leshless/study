#include <stdio.h>

struct Tree {
 int key;
 struct Tree *left;
 struct Tree *right;
};

size_t count(struct Tree* tree) {
    if (tree == NULL) {
        return 0;
    }

    return count(tree->left) + count(tree->right) + 1;
}

struct Tree* kth(struct Tree* tree, size_t k) {
    size_t cnt = count(tree->left);

    if (cnt > k){
        return kth(tree->left, k);
    }
    if (cnt < k) {
        return kth(tree->right,  k - cnt - 1);
    }

    return tree;
}

// Eсли не будет заходить по времени, то можно написать 
// свое дерево, у которого будут храниться размеры поддеревьев