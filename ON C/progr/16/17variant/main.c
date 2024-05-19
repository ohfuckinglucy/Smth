#include <stdio.h>
#include <stdlib.h>

// Определение структуры для узла списка
struct Node {
    int data;
    struct Node* next;
    struct Node* selected;
};

// Функция для создания нового узла
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->selected = NULL;
    return newNode;
}

// Функция для печати списка
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Функция для печати выделенного узла
void printSelected(struct Node* selected) {
    if (selected != NULL) {
        printf("Выделенный элемент: %d\n", selected->data);
    } else {
        printf("Выделенный элемент отсутствует\n");
    }
}

// Главная функция
int main() {
    struct Node* S = NULL;
    struct Node* last = NULL; // для хранения последнего введенного узла
    struct Node* current = NULL; // указатель для текущего узла
    int input;

    printf("Введите последовательность целых чисел, завершающуюся нулем:\n");

    // Ввод и создание списка
    while (1) {
        scanf("%d", &input);
        if (input == 0) {
            break;
        }
        struct Node* newNode = createNode(input);

        if (S == NULL) {
            S = newNode;
        } else {
            newNode->next = last;
        }

        last = newNode;
    }

    // Добавляем последний узел с нулем
    struct Node* zeroNode = createNode(0);
    zeroNode->next = last;

    // Назначаем S на узел с нулем, чтобы правильно закончить список
    S = zeroNode;

    printf("Сформированный список:\n");
    printList(S);

    // Навигация по списку
    current = S;
    char command;
    while (1) {
        printf("Введите команду (n - следующий элемент, q - выход): ");
        scanf(" %c", &command);

        if (command == 'n') {
            if (current != NULL) {
                current = current->next;
            }
            printSelected(current);
        } else if (command == 'q') {
            break;
        } else {
            printf("Неизвестная команда\n");
        }
    }

    // Очистка памяти
    current = S;
    struct Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    return 0;
}
