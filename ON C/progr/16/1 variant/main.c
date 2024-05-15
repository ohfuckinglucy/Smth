#include <stdio.h>
#include <stdlib.h>

// Структура для узла списка
struct Node {
    int data;                // Информационное поле
    struct Node* next;       // Поле для связи с последующим элементом в общем списке
    int isSecondListStart;   // Флаг, указывающий, является ли текущий элемент началом второго списка
};

// Функция для создания нового узла
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->isSecondListStart = 0; // По умолчанию текущий элемент не является началом второго списка
    return newNode;
}

// Функция для построения списков
void buildLists(int* sequence, int n, int k, struct Node** S) {
    struct Node** nodes = (struct Node**)malloc(n * sizeof(struct Node*));
    for (int i = 0; i < n; i++) {
        nodes[i] = createNode(sequence[i]);
    }
    
    // Построение общего списка
    for (int i = 0; i < n - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    nodes[n - 1]->next = NULL;  // Завершение общего списка

    // Помечаем начало второго списка
    nodes[k - 1]->isSecondListStart = 1;

    *S = nodes[0];  // Переменная S указывает на начало общего списка

    free(nodes);  // Освобождение временного массива
}

// Функция для перемещения по списку
void move(struct Node* node, int size){
    int count = 0;
    int count2 = 0;
    char command;
    struct Node* current = node;

    printf("Текущий элемент: %d\n", current->data);

    while (1) {
        command = getchar();
        if ((command == 'd') && (current->next != NULL)) {
            current = current->next;
            count2 += 1;
            printf("Текущий элемент: %d\n", current->data);
        } else if ((command == 's' && current->isSecondListStart) || ((command == 's') && (count != 0)) || ((command == 's') && (count2 == size))) {
            printf("Невозможно переместиться вниз.\n");
        } else if (command == 's' && current->next != NULL && !current->isSecondListStart  && (count == 0 )) {
            count += 1;
            current = current->next;
            printf("Текущий элемент: %d\n", current->data);
        } else if (command == 'q') {
            break;
        } else if((command == 'd') && (current->next == NULL)){
            printf("Невозможно переместиться дальше\n");
        } else if((command == 's') && (current->next == NULL)){
            printf("Невозможно переместиться дальше\n");
        }
    }
}

int main() {
    int *array = NULL; // Инициализируем указатель на массив
    int size = 0; // Инициализируем переменную для отслеживания размера массива
    int input; // Переменная для хранения ввода пользователя

    printf("Введите числа, 0 для завершения:\n");

    // Заполняем массив числами с клавиатуры
    do {
        scanf("%d", &input);

        if (input != 0) {
            // Увеличиваем размер массива
            size++;
            // Перевыделяем память под массив
            array = (int *)realloc(array, size * sizeof(int));
            // Проверка на успешное выделение памяти
            if (array == NULL) {
                printf("Ошибка выделения памяти!\n");
                return 1; // Выход из программы с ошибкой
            }
            // Записываем введенное число в массив
            array[size - 1] = input;
        }
    } while (input != 0);

    int k = size / 2;  // Разделяем последовательность на два списка
    struct Node* S;

    buildLists(array, size, k, &S);

    // Запуск функции move для перемещения по списку
    printf("Для движения вниз нажмите s\nДля движения вправо нажмите d\nДля выхода из программы нажмите q\n(другие символы восприниматься не будут)\n");
    move(S, size);

    // Освобождаем память, выделенную под массив
    free(array);

    return 0;
}