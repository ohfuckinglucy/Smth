#include <iostream>
#include <cstring>
#include "header.h"

using namespace std;

void left_rotate(rbtree *&root, rbtree *x) {
    rbtree *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(rbtree *&root, rbtree *x) {
    rbtree *y = x->left;
    x->left = y->right;
    if (y->right != nullptr) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

rbtree* rbtree_add(rbtree *root, int key, char *value) {
    rbtree *node = new rbtree(key, value);
    
    if (root == nullptr) {
        node->color = BLACK;
        return node;
    }
    
    rbtree *y = nullptr;
    rbtree *x = root;
    while (x != nullptr) {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    
    node->parent = y;
    if (node->key < y->key)
        y->left = node;
    else
        y->right = node;
    
    // Балансировка
    // Функция fix_add описывает алгоритм балансировки дерева после вставки
    fix_add(root, node);
    
    return root;
}

void fix_add(rbtree *&root, rbtree *node) {
    while (node != root && node->parent->color == RED) {
        rbtree *uncle;
        if (node->parent == node->parent->parent->left) {
            uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(root, node->parent->parent);
            }
        } else {
            uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                left_rotate(root, node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

rbtree* rbtree_lookup(rbtree *root, int key) {
    while (root != nullptr && key != root->key) {
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

void transplant(rbtree *&root, rbtree *u, rbtree *v) {
    if (u->parent == nullptr) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    if (v != nullptr) v->parent = u->parent;
}

void fix_delete(rbtree *&root, rbtree *x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == x->parent->left) {
            rbtree *w = x->parent->right; // Брат x

            if (w->color == RED) { // Случай 1: брат красный
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(root, x->parent);
                w = x->parent->right;
            }

            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) { // Случай 2: оба ребенка брата чёрные
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == nullptr || w->right->color == BLACK) { // Случай 3: левый ребенок брата красный
                    if (w->left != nullptr) w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color; // Случай 4: правый ребенок брата красный
                x->parent->color = BLACK;
                if (w->right != nullptr) w->right->color = BLACK;
                left_rotate(root, x->parent);
                x = root;
            }
        } else { // Симметрично для правого ребенка
            rbtree *w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(root, x->parent);
                w = x->parent->left;
            }

            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    if (w->right != nullptr) w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != nullptr) w->left->color = BLACK;
                right_rotate(root, x->parent);
                x = root;
            }
        }
    }

    if (x != nullptr) x->color = BLACK;
}

// Функция для измерения высоты дерева
int tree_height(rbtree *node) {
    if (node == nullptr) return 0;
    int left_height = tree_height(node->left);
    int right_height = tree_height(node->right);
    return max(left_height, right_height) + 1;
}

rbtree* rbtree_delete(rbtree *root, int key) {
    if (root == nullptr) {
        cout << "Ошибка: Дерево пустое." << endl;
        return nullptr;
    }

    rbtree *node = rbtree_lookup(root, key);
    if (node == nullptr) {
        cout << "Ошибка: Узел с ключом " << key << " не найден." << endl;
        return root;
    }

    cout << "Удаление узла с ключом: " << key << endl;
    
    rbtree *y = node;
    rbtree *x;
    Color original_color = y->color;

    if (node->left == nullptr) {
        x = node->right;
        transplant(root, node, node->right);
    } else if (node->right == nullptr) {
        x = node->left;
        transplant(root, node, node->left);
    } else {
        y = rbtree_min(node->right);
        original_color = y->color;
        x = y->right;
        if (y->parent == node) {
            if (x != nullptr) {
                x->parent = y;
            }
        } else {
            transplant(root, y, y->right);
            y->right = node->right;
            if (y->right != nullptr) {
                y->right->parent = y;
            }
        }
        transplant(root, node, y);
        y->left = node->left;
        if (y->left != nullptr) {
            y->left->parent = y;
        }
        y->color = node->color;
    }

    delete node;  // Убедимся, что удаляем узел после всех операций

    if (original_color == BLACK) {
        fix_delete(root, x);
    }

    return root;
}


rbtree* rbtree_min(rbtree *root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

rbtree* rbtree_max(rbtree *root) {
    while (root->right != nullptr)
        root = root->right;
    return root;
}

void rbtree_print_dfs(rbtree *root, int level) {
    if (root == nullptr) return;
    rbtree_print_dfs(root->right, level + 1);
    for (int i = 0; i < level; i++) cout << "   ";
    cout << root->key << "(" << (root->color == RED ? "R" : "B") << ")" << endl;
    rbtree_print_dfs(root->left, level + 1);
}

void rbtree_free(rbtree *root) {
    if (root == nullptr) return;
    rbtree_free(root->left);
    rbtree_free(root->right);
    free(root->value);
    delete root;
}
