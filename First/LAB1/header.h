#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <cstring>

// Определение цвета узла
enum Color { RED, BLACK };

// Определение структуры rbtree
struct rbtree {
    int key;
    char* value;
    Color color;
    rbtree *left, *right, *parent;

    rbtree(int k, char* v) : key(k), value(strdup(v)), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Прототипы функций
void left_rotate(rbtree *&root, rbtree *x);
void right_rotate(rbtree *&root, rbtree *x);
rbtree* rbtree_add(rbtree *root, int key, char *value);
void fix_add(rbtree *&root, rbtree *node);
rbtree* rbtree_lookup(rbtree *root, int key);
void transplant(rbtree *&root, rbtree *u, rbtree *v);
void fix_delete(rbtree *&root, rbtree *x);
rbtree* rbtree_delete(rbtree *root, int key);
rbtree* rbtree_min(rbtree *root);
rbtree* rbtree_max(rbtree *root);
int tree_height(rbtree *node);
void rbtree_print_dfs(rbtree *root, int level);
void rbtree_free(rbtree *root);

#endif // RBTREE_H
