#include <iostream>

using namespace std;
class Node {
public:
    double data;
    Node* prev, * next;

public:
    Node(double data) {
        this->data = data;
        this->prev = this->next = NULL;
    }
};

class LinkedList {
public:
    Node *head, * tail;

public:
    LinkedList() {
        head = tail = NULL;
    }
    
    ~LinkedList() {
        while (head != NULL)
            pop_front();
    }

    Node* push_front(double data) {
        Node* ptr = new Node(data);
        ptr->next = head;
        if (head != NULL) {
            head->prev = ptr;
        }
        if (tail == NULL) {
            tail = ptr;
        }

        head = ptr;

        return ptr;
    }
    Node* push_back(double data) {
        Node* ptr = new Node(data);
        ptr->prev = tail;
        if (tail != NULL) {
            tail->next = ptr;
        }

        if (head == NULL) {
            head = ptr;
        }

        tail = ptr;

        return ptr;
    }
    void pop_front() {
        if (head == NULL) return;

        Node* ptr = head->next;

        if (ptr != NULL) {
            ptr->prev = NULL;
        }
        else tail = NULL;

        delete head;
        head = ptr;
    }

    void pop_back() {
        if (tail == NULL) return;

        Node* ptr = tail->prev;

        if (ptr != NULL) {
            ptr->next = NULL;
        }
        else head = NULL;

        delete tail;
        tail = ptr;
    }

    Node* getAt(int index) {
        Node* ptr = head;
        int n = 0;

        while (n != index) {
            if (ptr == NULL) return ptr;
            ptr = ptr->next;
            n++;
        }

        return ptr;
    }

    Node* operator [] (int index) {
        return getAt(index);
    }

    Node* insert(int index, double data) {
        Node* right = getAt(index);
        if (right == NULL) return push_back(data);

        Node* left = right->prev;
        if (left == NULL) return push_front(data);

        Node* ptr = new Node(data);

        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;

        return ptr;
    }

    void erase(int index) {
        Node* ptr = getAt(index);
        if (ptr == NULL) return;

        if (ptr->prev == NULL) {
            pop_front();
            return;
        }
        if (ptr->next == NULL) {
            pop_back();
            return;
        }

        Node* left = ptr->prev;
        Node* right = ptr->next;
        left->next = right;
        right->prev = left;

        delete ptr;
    }
};

int main()
{
    LinkedList lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    for (Node* ptr = lst.head; ptr != NULL; ptr = ptr->next) {
        cout << ptr->data << " ";
    }cout << endl;
    for (Node* ptr = lst.tail; ptr != NULL; ptr = ptr->prev) {
        cout << ptr->data << " ";
    }cout << endl;

    return 0;
}