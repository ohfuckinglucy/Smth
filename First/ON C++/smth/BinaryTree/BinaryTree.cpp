#include <iostream>
#include <ncurses.h>
#include <curses.h>

using namespace std;



struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        this->left = this->right = NULL;
    }
};

class BinaryTree {
public:
    Node* root;
    Node* current;
    
    BinaryTree() {
        this->root = this->current = NULL;
    }

public:
    // Рекурсивная функция для вставки значения в бинарное дерево
    Node* insertin(Node* root, int value) {
        // Если дерево пустое, создаем новый узел и делаем его корнем
        if (root == NULL) {
            return new Node(value);
        }

        // Иначе рекурсивно ищем место для вставки значения
        if (value < root->data) {
            root->left = insertin(root->left, value);
        }
        else if (value > root->data) {
            root->right = insertin(root->right, value);
        }

        return root;
    }

    // Вспомогательная функция для поиска родительского узла
    Node* findParent(Node* root, int value) {
        if (root == NULL || (root->left != NULL && root->left->data == value) || (root->right != NULL && root->right->data == value)) {
            return root;
        }

        if (value < root->data) {
            return findParent(root->left, value);
        }
        else {
            return findParent(root->right, value);
        }
    }

    void setCurrentToRoot() {
        current = root;
    }
    // Метод для вставки значения в дерево
    void insert(int value) {
        root = insertin(root, value);
    }

    // Метод для перемещения указателя текущего узла вверх
    void moveUp() {
        if (current != NULL && current != root) {
            Node* parent = findParent(root, current->data);
            if (parent != NULL) {
                current = parent;
            }
        }
    }

    // Метод для перемещения указателя текущего узла вниз (на левого потомка)
    void moveDownLeft() {
        if (current != NULL && current->left != NULL) {
            current = current->left;
        }
    }

    // Метод для перемещения указателя текущего узла вниз (на правого потомка)
    void moveDownRight() {
        if (current != NULL && current->right != NULL) {
            current = current->right;
        }
    }

    // Метод для вывода значения текущего узла
    void printCurrent() {
        if (current != NULL) {
            cout << "Текущий узел: " << current->data << endl;
        }
        else {
            cout << "Дерево пустое или указатель не установлен." << endl;
        }
    }
    Node* minValueNode(Node* node) {
        Node* current = node;

        // Идем к самому левому узлу дерева
        while (current->left != NULL) {
            current = current->left;
        }

        return current;
    }
    Node* deleteNode(Node* root, int value) {
        // Если дерево пустое, возвращаем nullptr
        if (root == NULL) {
            return root;
        }

        // Если значение меньше значения текущего узла, рекурсивно удаляем из левого поддерева
        if (value < root->data) {
            root->left = deleteNode(root->left, value);
        }
        // Если значение больше значения текущего узла, рекурсивно удаляем из правого поддерева
        else if (value > root->data) {
            root->right = deleteNode(root->right, value);
        }
        // Если значение равно значению текущего узла, это узел для удаления
        else {
            // Узел с одним или без потомков
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Узел с двумя потомками
            // Находим узел с наименьшим значением в правом поддереве (или наибольшим в левом поддереве)
            Node* temp = minValueNode(root->right);

            // Копируем значение найденного узла в текущий узел
            root->data = temp->data;

            // Рекурсивно удаляем найденный узел
            root->right = deleteNode(root->right, temp->data);
        }

        return root;
    }
    void deleteElement(int value){
        deleteNode(root, value);
    }
};

int main() {
    initscr();
    
    setlocale(LC_ALL, "Russian");

    BinaryTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    tree.deleteElement(3);

    tree.setCurrentToRoot();

    char key;
    do {
        clear();
        tree.printCurrent();
        cout << "Используйте клавиши WAD для навигации по дереву (Q - выход):\nИ не забудьте переключить раскладку на англйиский язык!!!" << endl;
        key = getch();
        getch();

        switch (key) {
        case 'w':
        case 'W':
            tree.moveUp();
            break;
        case 'a':
        case 'A':
            tree.moveDownLeft();
            break;
        case 'd':
        case 'D':
            tree.moveDownRight();
            break;
        }
    } while (key != 'q' && key != 'Q');

    return 0;
}