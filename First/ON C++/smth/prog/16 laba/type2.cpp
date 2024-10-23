#include <iostream>

using namespace std;

class Node {
public:
    double data;
    Node* next;

public:
    Node(double data) {
        this->data = data;
        this->next = NULL;
    }
};

class OneLinkedList {
public:
    Node* head, * tail;

public:
    OneLinkedList() {
        this->head = this->tail = NULL;
    }

    ~OneLinkedList() {
        while (head != NULL) pop_front();
    }

    void pop_front(){ // Удаление первого элемента односвязного списка
        if (head == NULL) return;
        if (head == tail) {
            delete tail;
            head = tail = NULL;
            return;
        }
        Node* node = head;
        head = node->next;
        delete node;
    }

    void push_back(double data) { // Добавление в конец
        Node* node = new Node(data);
        if (head == NULL) head = node;
        if (tail != NULL) tail->next = node;
        tail = node;
    }

    void push_front(double data){ // Добавление в начало
        Node* node = new Node(data);
        node->next = head;
        head = node;
        if (tail == NULL) tail = node;
    }

    void pop_back() { // Удаление с конца
        if (tail == NULL) return;
        if (head == tail) {
            delete tail;
            head = tail = NULL;
            return;
        }

        Node* node = head;
        for (;node->next != tail; node = node->next);
        node->next = NULL;
        delete tail;
        tail = node;
    }

    Node* getAt(int k) {
        if (k < 0) return NULL;
        
        Node* node = head;
        int n = 0;
        while (node != NULL && n != k && node->next != NULL) {
            node = node->next;
            n++;
        }
        return(n == k) ? node : NULL;
    }

    void insert(int k, double data) {
        Node* left = getAt(k);
        if (left == NULL) return;

        Node* right = left->next;
        Node* node = new Node(data);

        left->next = node;
        node->next = right;

        if (right == NULL) tail = node;
    }

    void erase(int k) {
        if (k < 0) return;
        if (k == 0) {
            pop_front();
            return;
        }
        Node* left = getAt(k - 1);
        Node* node = left->next;
        if (node == NULL) return;
        Node* right = node->next;

        left->next = right;
        if (node == tail) tail = left;
        delete node;
    }
};


int main()
{
    OneLinkedList lst;
    lst.push_front(1);
    lst.push_back(2);

    Node* n = lst.getAt(0);
    double d = (n != NULL) ? n->data : 0;

    for (Node* node = lst.head; node != NULL; node = node->next) {
        cout << node->data << "";
    }

    cout << endl;

    lst.erase(1);
    lst.insert(0, 5);
    lst.insert(0, 2);

    cout << d << endl;
}
