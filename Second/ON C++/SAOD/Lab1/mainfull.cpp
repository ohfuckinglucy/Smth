#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum { RED, BLACK } Color;

typedef struct rbtree {
    int key;
    char *value;
    Color color;
    struct rbtree *left, *right, *parent;
} rbtree;

rbtree *create_node(int key, const char *value) {
    rbtree *node = (rbtree *)malloc(sizeof(rbtree));
    node->key = key;
    node->value = strdup(value); // Дублируем строку для хранения в узле
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void left_rotate(rbtree **root, rbtree *x) {
    rbtree *y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(rbtree **root, rbtree *y) {
    rbtree *x = y->left;
    y->left = x->right;
    if (x->right != NULL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void rbtree_add_fixup(rbtree **root, rbtree *node) {
    while (node != *root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            rbtree *uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
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
            rbtree *uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
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
    (*root)->color = BLACK;
}

rbtree *rbtree_add(rbtree *root, int key, const char *value) {
    rbtree *parent = NULL;
    rbtree *node = root;
    
    while (node != NULL) {
        parent = node;
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            free(parent->value); 
            parent->value = strdup(value); 
            return root;
        }
    }
    
    rbtree *new_node = create_node(key, value);
    new_node->parent = parent;
    
    if (parent == NULL) {
        root = new_node;
    } else if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    
    rbtree_add_fixup(&root, new_node);
    
    return root;
}

rbtree *rbtree_lookup(rbtree *root, int key) {
    while (root != NULL) {
        if (key < root->key) {
            root = root->left;
        } else if (key > root->key) {
            root = root->right;
        } else {
            return root;  // Найден узел с нужным ключом
        }
    }
    return NULL;  // Узел не найден
}

rbtree *rbtree_min(rbtree *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}


rbtree *rbtree_max(rbtree *root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

void rbtree_free(rbtree *root) {
    if (root != NULL) {
        rbtree_free(root->left);
        rbtree_free(root->right);
        free(root->value);
        free(root);
    }
}

void print_branch(const char *prefix, const rbtree *node, int is_left) {
    if (node != NULL) {
        printf("%s", prefix);
        printf(is_left ? "├──" : "└──");
        printf(" %d (%s)\n", node->key, node->color == RED ? "RED" : "BLACK");

        char new_prefix[128];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "│   " : "    ");
        print_branch(new_prefix, node->left, 1);
        print_branch(new_prefix, node->right, 0);
    }
}

void rbtree_print(const rbtree *root) {
    if (root != NULL) {
        print_branch("", root, 0);
    }
}

void rbtree_transplant(rbtree **root, rbtree *u, rbtree *v) {
    if (u->parent == NULL) {
        *root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

void rbtree_delete_fixup(rbtree **root, rbtree *x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            rbtree *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(root, x->parent);
                x = *root;
            }
        } else {
            rbtree *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}


rbtree *rbtree_delete(rbtree *root, int key) {
    rbtree *z = rbtree_lookup(root, key);
    if (z == NULL) {
        return root; // Узел с таким ключом не найден
    }

    rbtree *y = z;
    Color original_color = y->color;
    rbtree *x;

    if (z->left == NULL) {
        x = z->right;
        rbtree_transplant(&root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        rbtree_transplant(&root, z, z->left);
    } else {
        y = rbtree_min(z->right);
        original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) x->parent = y;
        } else {
            rbtree_transplant(&root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbtree_transplant(&root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z->value);
    free(z);

    if (original_color == BLACK && x != NULL) {
        rbtree_delete_fixup(&root, x);
    }

    return root;
}

// Функция для расчета высоты дерева
int rbtree_height(rbtree *node) {
    if (node == NULL) {
        return 0;
    } else {
        int left_height = rbtree_height(node->left);
        int right_height = rbtree_height(node->right);
        return (left_height > right_height ? left_height : right_height) + 1;
    }
}


int main() {
    rbtree *root = NULL;

    // Вставляем узлы и выводим высоту дерева после каждой серии вставок
    int steps[] = {100, 1000, 5000, 10000, 20000, 50000}; // Количество узлов для проверки
    for (int s = 0; s < sizeof(steps) / sizeof(steps[0]); s++) {
        printf("Добавляем %d элементов...\n", steps[s]);
        for (int i = 1; i <= steps[s]; i++) {
            char value[20];
            snprintf(value, sizeof(value), "Value%d", i);
            root = rbtree_add(root, i, value);
        }
        printf("Высота дерева после добавления %d элементов: %d\n", steps[s], rbtree_height(root));
    }

    // Демонстрация работы функции rbtree_lookup
    printf("\nПроверка поиска ключей в дереве:\n");
    for (int key = 1; key <= 50000; key *= 10) {
        rbtree *found_node = rbtree_lookup(root, key);
        if (found_node != NULL) {
            printf("Ключ %d найден, значение: %s\n", key, found_node->value);
        } else {
            printf("Ключ %d не найден\n", key);
        }
    }

// Удаление узлов
    printf("\nУдаление узлов:\n");
    srand(time(NULL)); // Инициализация генератора случайных чисел
    for (int i = 0; i < 10; i++) {
        int key_to_delete = rand() % 50000 + 1;
        printf("Удаление узла с ключом %d\n", key_to_delete);
        root = rbtree_delete(root, key_to_delete);

        // Проверка с помощью rbtree_lookup
        rbtree *result = rbtree_lookup(root, key_to_delete);
        if (result == NULL) {
            printf("Узел с ключом %d успешно удалён\n", key_to_delete);
        } else {
            printf("Ошибка: узел с ключом %d найден после удаления\n", key_to_delete);
        }
    }

    // rbtree_print(root);

// Очистка дерева
rbtree_free(root);

return 0;

}
