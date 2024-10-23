#include <stdio.h>
#include <stdlib.h>

// Определение структуры для узла односвязного списка
typedef struct SingleNode {
    int data;                  // Информационное поле
    struct SingleNode* next;   // Указатель на следующий элемент
} SingleNode;

// Определение структуры для узла двусвязного списка
typedef struct DoubleNode {
    struct DoubleNode* next;   // Указатель на следующий элемент
    struct DoubleNode* prev;   // Указатель на предыдущий элемент
    SingleNode* singleList;    // Указатель на односвязный список
} DoubleNode;

// Функция для создания нового узла односвязного списка
SingleNode* createSingleNode(int data) {
    SingleNode* newNode = (SingleNode*)malloc(sizeof(SingleNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Функция для создания нового узла двусвязного списка
DoubleNode* createDoubleNode() {
    DoubleNode* newNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->singleList = NULL;
    return newNode;
}

// Функция для добавления нового узла в односвязный список
void appendToSingleList(SingleNode** head, int data) {
    SingleNode* newNode = createSingleNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        SingleNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Функция для добавления нового узла в двусвязный список
void appendToDoubleList(DoubleNode** head) {
    DoubleNode* newNode = createDoubleNode();
    if (*head == NULL) {
        *head = newNode;
    } else {
        DoubleNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Функция для печати данных односвязного списка
void printSingleList(SingleNode* head) {
    SingleNode* current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

// Функция для навигации по двусвязному списку и печати данных односвязного списка
void navigateDoubleList(DoubleNode* head) {
    DoubleNode* current = head;
    char command;
    while (current != NULL) {
        printSingleList(current->singleList);
        printf("Вправо d\nВлево a\nВыход из программы q\n");
        command = getchar();
        while (command == '\n') {
            command = getchar();
        }
        if (command == 'd') {
            if (current->next != NULL) {
                current = current->next;
            } else {
                printf("Конец списка\n");
            }
        } else if (command == 'a') {
            if (current->prev != NULL) {
                current = current->prev;
            } else {
                printf("Начало списка\n");
            }
        } else if (command == 'q'){
            break;
        } else {
            printf("Неверная команда\n");
        }
    }
}

// Основная функция программы
int main() {
    DoubleNode* head = NULL;  // Начальный узел двусвязного списка
    DoubleNode* currentNode = NULL;
    int value;

    printf("введите элементы списка для завершения введите 0\n");
    while (1) {
        scanf("%d", &value);
        if (value == 0) {
            break;
        }
        if (head == NULL) {
            appendToDoubleList(&head);
            currentNode = head;
        } else if (currentNode->singleList != NULL) {
            appendToDoubleList(&(currentNode->next));
            currentNode->next->prev = currentNode;
            currentNode = currentNode->next;
        }
        appendToSingleList(&(currentNode->singleList), value);
    }

    navigateDoubleList(head);  // Навигация по двусвязному списку и вывод данных из односвязного списка

    return 0;
}
