#include <iostream>
#include <sys/time.h>
#include <cstring>

class bstree {
public:
    char* key;
    int value;
    struct bstree *left;
    struct bstree *right;

    // Конструктор
    bstree(char* key, int value) {
        this->key = strdup(key);
        this->value = value;
        this->left = this->right = NULL;
    }

    // Метод добавления элемента в дерево
    void bstree_add(struct bstree *tree, char* key, int value) {
        if (tree == NULL)
            return;
        struct bstree *parent, *node;
        while (tree != NULL) {
            parent = tree;
            if (strcmp(key, tree->key) < 0)
                tree = tree->left;
            else if (strcmp(key, tree->key) > 0)
                tree = tree->right;
            else
                return;
        }
        node = new bstree(key, value);
        if (strcmp(key, parent->key) < 0)
            parent->left = node;
        else
            parent->right = node;
    }

    // Метод поиска элемента в дереве по ключу
    struct bstree *bstree_lookup(struct bstree *tree, char* key) {
        while (tree != NULL) {
            if (strcmp(key, tree->key) == 0)
                return tree;
            else if (strcmp(key, tree->key) < 0)
                tree = tree->left;
            else
                tree = tree->right;
        }
        return tree;
    }

    // Метод поиска минимального элемента в дереве
    struct bstree *bstree_min(struct bstree *tree) {
        if (tree == NULL)
            return NULL;
        while (tree->left != NULL)
            tree = tree->left;
        return tree;
    }

    // Метод поиска максимального элемента в дереве
    struct bstree *bstree_max(struct bstree *tree) {
        if (tree == NULL)
            return NULL;
        while (tree->right != NULL)
            tree = tree->right;
        return tree;
    }

    // Метод удаления элемента из дерева
    void bstree_delete(struct bstree *tree, char* key) {
        struct bstree *parent = NULL;
        struct bstree *current = tree;
        while (current != NULL && strcmp(current->key, key) != 0) {
            parent = current;
            if (strcmp(key, current->key) < 0)
                current = current->left;
            else
                current = current->right;
        }

        if (current == NULL)
            return;

        if (current->left == NULL && current->right == NULL) {
            if (parent == NULL)
                tree = NULL;
            else if (parent->left == current)
                parent->left = NULL;
            else
                parent->right = NULL;
            delete current;
        } else if (current->left == NULL || current->right == NULL) {
            struct bstree *child = (current->left != NULL) ? current->left : current->right;
            if (parent == NULL)
                tree = child;
            else if (parent->left == current)
                parent->left = child;
            else
                parent->right = child;
            delete current;
        } else {
            struct bstree *successor = bstree_min(current->right);
            current->key = strdup(successor->key);
            current->value = successor->value;
            bstree_delete(current->right, successor->key);
        }
    }
};

// Функция для получения текущего времени
double wtime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

// Функция для генерации случайного числа в заданном диапазоне
int getrand(int min, int max) {
    return rand() % (max - min + 1) + min;
}