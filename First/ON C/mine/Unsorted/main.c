#include <stdio.h>
#include <stdlib.h>

// Структура элемента однонаправленного списка
typedef struct SingleListNode {
    int data;
    struct SingleListNode* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти для узла\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

typedef struct TripleListNode {
    struct SingleListNode* first;
    struct SingleListNode* second;
    struct TripleListNode* next;
    struct TripleListNode* head, * tail;
} TNode;

TNode* createTNode() {
    TNode* newNode = (TNode*)malloc(sizeof(TNode));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти для узла\n");
        exit(1);
    }
    newNode->first = newNode->second = NULL;
    newNode->next = NULL;
    newNode->head = newNode->tail = NULL;
    return newNode;
}

void pushlinker(TNode** head, TNode** tail) {
    TNode* Linker = createTNode();
    if ((*head) == NULL) {
        (*head) = (*tail) = Linker;
    } else {
        (*tail)->next = Linker;
        (*tail) = Linker;
    }
}


void pushdata(TNode* head, int data) {
    Node* newNode = createNode(data);

    if (head->first == NULL) {
        head->first = newNode;
    } else if (head->second == NULL) {
        head->second = newNode;
    } else {
        Node* temp = head->first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}



void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void deleteExtraNodes(TNode* head) {
    if (head == NULL || head->first == NULL || head->second == NULL)
        return;

    Node* first = head->first;
    Node* second = head->second;

    int count1 = 0, count2 = 0;
    while (first != NULL) {
        count1++;
        first = first->next;
    }
    while (second != NULL) {
        count2++;
        second = second->next;
    }

    if (count1 > count2) {
        int diff = count1 - count2;
        first = head->first;
        while (diff > 0) {
            Node* temp = first;
            first = first->next;
            free(temp);
            diff--;
        }
        head->first = first;
    } else if (count2 > count1) {
        int diff = count2 - count1;
        second = head->second;
        while (diff > 0) {
            Node* temp = second;
            second = second->next;
            free(temp);
            diff--;
        }
        head->second = second;
    }
}

int main() {
    TNode* Linker = createTNode();

    int data;
    int i = 0;

    printf("Введите числа для добавления в списки (для завершения ввода нажмите '-1'): \n");
    while (1) {
        scanf("%d", &data);
        if (data == -1) // Для завершения ввода
            break;
        if (i % 2 == 0) 
            pushdata(Linker, data);
        else 
            pushdata(Linker, data);
        i++;
    }





    // Проверяем и удаляем лишние узлы
    deleteExtraNodes(Linker);

    // Выводим результаты
    printf("Верхний список: ");
    printList(Linker->first);
    printf("Нижний список: ");
    printList(Linker->second);

    return 0;
}
