#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int key, value;
    Color color;
    Node *left, *right, *parent;

    Node(int k, int v) : key(k), value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct RBTree {
    Node* root;

    RBTree() : root(nullptr) {}

    void RBTree_Add(int key, int value);
    void RBTree_Add_Fixup(Node* node);

private:
    void LeftRotate(Node* x);
    void RightRotate(Node* y);
};

void RBTree::RBTree_Add(int key, int value) {
    Node* tree = root;
    Node* parent = nullptr;

    // Ищем подходящее место для нового узла
    while (tree != nullptr) {
        parent = tree;
        if (key < tree->key)
            tree = tree->left;
        else if (key > tree->key)
            tree = tree->right;
        else
            return; // Ключ уже существует
    }

    // Создаем новый узел
    Node* node = new Node(key, value);
    node->parent = parent;

    // Если дерево пустое, новый узел становится корнем
    if (parent == nullptr) {
        root = node;
    } else {
        // Вставляем узел в нужное место
        if (key < parent->key)
            parent->left = node;
        else
            parent->right = node;
    }

    // Устанавливаем цвет узла в красный и исправляем дерево
    node->color = RED;
    RBTree_Add_Fixup(node);
}

void RBTree::RBTree_Add_Fixup(Node* node) {
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == RED) {
                // Случай 1: дядя красный
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Случай 2: узел - правый ребенок
                    node = node->parent;
                    LeftRotate(node);
                }
                // Случай 3: узел - левый ребенок
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RightRotate(node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == RED) {
                // Случай 1: дядя красный
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    // Случай 2: узел - левый ребенок
                    node = node->parent;
                    RightRotate(node);
                }
                // Случай 3: узел - правый ребенок
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                LeftRotate(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::LeftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y; // Если x был корнем, то y становится новым корнем
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBTree::RightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x; // Если y был корнем, то x становится новым корнем
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

int main() {
    RBTree tree;
    tree.RBTree_Add(10, 100);
    tree.RBTree_Add(20, 200);
    tree.RBTree_Add(30, 300);
    // Добавьте тесты и проверьте корректность работы дерева
    return 0;
}