#include <cstring>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <chrono>

using namespace std;

class Node {
public:
    char* key;
    uint32_t value;
    Node *left, *right;

    Node(const string& key, uint32_t value) : key(nullptr), value(value), left(nullptr), right(nullptr) {
        this->key = new char[key.length() + 1];
        strcpy(this->key, key.c_str());
    }

    ~Node() {
        delete[] key;
    }

    void add(Node*& tree, const string& key, uint32_t value) {
        Node* parent = nullptr;
        Node* current = tree;

        while (current != nullptr) {
            parent = current;

            if (!key.empty() && strcmp(key.c_str(), current->key) < 0) {
                current = current->left;
            }
            else if (strcmp(key.c_str(), current->key) > 0)
                current = current->right;
            else {
                current->value = value;
                return;
            }
        }

        Node* newNode = new Node(key, value);

        if (parent == nullptr)
            tree = newNode;
        else if (strcmp(key.c_str(), parent->key) < 0)
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    Node* bstree_delete(Node*& tree, const string& key) {
        if (tree == nullptr) {
            return nullptr;
        }

        if (strcmp(key.c_str(), tree->key) < 0) {
            tree->left = bstree_delete(tree->left, key);
        } else if (strcmp(key.c_str(), tree->key) > 0) {
            tree->right = bstree_delete(tree->right, key);
        } else {
            if (tree->left == nullptr && tree->right == nullptr) {
                delete tree;
                tree = nullptr;
            } else if (tree->left == nullptr) {
                Node* temp = tree;
                tree = tree->right;
                delete temp;
            } else if (tree->right == nullptr) {
                Node* temp = tree;
                tree = tree->left;
                delete temp;
            } else {
                Node* min_right_subtree = tree_min(tree->right);
                delete[] tree->key;
                tree->key = new char[strlen(min_right_subtree->key) + 1];
                strcpy(tree->key, min_right_subtree->key);
                tree->value = min_right_subtree->value;
                tree->right = bstree_delete(tree->right, min_right_subtree->key);
            }
        }

        return tree;
    }

    Node* LookUp(Node* tree, const std::string& key) {
        while (tree != nullptr) {
            int comparison = strcmp(key.c_str(), tree->key);

            if (comparison > 0)
                tree = tree->right;
            else if (comparison < 0)
                tree = tree->left;
            else
                return tree;
        }

        return nullptr;
    }

    Node* tree_min(Node* tree) {
        while (tree->left != nullptr) {
            tree = tree->left;
        }

        return tree;
    }
    Node* tree_max(Node* tree){
        while(tree->right != nullptr){
            tree = tree->right;
        }

        return tree;
    }
};

int getRand(int min, int max) {
    return min + rand() % (max - min + 1);
}
double wtime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}