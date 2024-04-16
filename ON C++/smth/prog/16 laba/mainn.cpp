#include <iostream>
#include <ncurses.h> // Для работы с curses в Linux

using namespace std;

class OneNode {
public:
    int data;
    OneNode* next;

    OneNode(int data) {
        this->data = data;
        this->next = NULL;
    }
};

class TripleNode {
public:
    OneNode* first, * second;
    TripleNode* next;

    TripleNode() {
        this->next = NULL;
        this->first = NULL;
        this->second = NULL;
    }
};

class LinkedList {
public:
    OneNode* FirstHead, * FirstTail;
    OneNode* SecondHead, * SecondTail;
    TripleNode* head, * tail;
    char currentDirection; // Текущее направление движения

    LinkedList() {
        head = tail = NULL;
        FirstHead = FirstTail = SecondTail = SecondHead = NULL;
        currentDirection = 'w'; // Начальное направление движения - вверх
    }

    void CreateTripleNode(OneNode* firstHead, OneNode* firstTail, OneNode* secondHead, OneNode* secondTail) {
        TripleNode* node = new TripleNode();
        node->first = firstHead;
        node->second = secondHead;

        if (firstTail != NULL && secondTail == NULL) {
            node->second = NULL;
        }
        else if (firstTail == NULL && secondTail != NULL) {
            node->first = NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }

        tail->next = head;
    }

    void CreateOneFirstNode(int data) {
        OneNode* node = new OneNode(data);
        if (FirstHead == NULL) FirstHead = node;
        if (FirstTail != NULL) FirstTail->next = node;
        FirstTail = node;
    }

    void CreateOneSecondNode(int data) {
        OneNode* node = new OneNode(data);
        if (SecondHead == NULL) SecondHead = node;
        if (SecondTail != NULL) SecondTail->next = node;
        SecondTail = node;
    }

    void MoveAlongLists() {
        TripleNode* tripleNode = head;
        while (true) {
            clear; // Очистить консоль (для Linux используйте "clear")
            cout << "Values in TripleNode: " << endl;
            cout << "First: ";
            if (tripleNode->first != NULL) {
                OneNode* firstNode = tripleNode->first;
                while (firstNode != NULL) {
                    cout << firstNode->data << " ";
                    firstNode = firstNode->next;
                }
            }
            cout << endl;
            cout << "Second: ";
            if (tripleNode->second != NULL) {
                OneNode* secondNode = tripleNode->second;
                while (secondNode != NULL) {
                    cout << secondNode->data << " ";
                    secondNode = secondNode->next;
                }
            }
            cout << endl;

            char input = getch(); // Получить нажатую клавишу (для Linux)

            // Изменение направления в зависимости от нажатой клавиши
            switch (input) {
            case 'w':
                tripleNode = tripleNode->next;
                break;
            case 'a':
                tripleNode = tripleNode->next;
                break;
            case 's':
                tripleNode = tripleNode->next;
                break;
            case 'd':
                tripleNode = tripleNode->next;
                break;
            default:
                break;
            }
        }
    }
};

int main() {
    LinkedList list;
    int n = 0;
    int m = 0;

    cout << "Введите элементы первой последовательности (введите -1 для завершения):" << endl;
    int input;
    cin >> input;
    while (input != -1) {
        list.CreateOneFirstNode(input);
        n++;
        cin >> input;
    }

    cout << "Введите элементы второй последовательности (введите -1 для завершения):" << endl;
    cin >> input;
    while (input != -1) {
        list.CreateOneSecondNode(input);
        m++;
        cin >> input;
    }

    list.CreateTripleNode(list.FirstHead, list.FirstTail, list.SecondHead, list.SecondTail);

    list.MoveAlongLists();

    return 0;
}