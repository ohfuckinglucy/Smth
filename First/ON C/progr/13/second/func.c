#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int* a, int* b, int* swaps) {
    int temp = *a;
    *a = *b;
    *b = temp;
    (*swaps)++;
}

void fillArray(int arr[], int n, int fillType) {
    switch (fillType) {
        case 1: // Ввод с клавиатуры
            printf("Введите %d элементов массива:\n", n);
            for (int i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
            }
            break;
        case 2: // Случайные числа
            srand(time(NULL));
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100; // Генерация случайных чисел от 0 до 99
            }
            break;
        case 3: // Из файла
            {
                FILE* file = fopen("input.txt", "r");
                if (file == NULL) {
                    printf("Не удалось открыть файл input.txt\n");
                    exit(1);
                }

                for (int i = 0; i < n; i++) {
                    fscanf(file, "%d", &arr[i]);
                }

                fclose(file);
            }
            break;
        default:
            printf("Некорректный тип заполнения массива\n");
            exit(1);
    }
}
