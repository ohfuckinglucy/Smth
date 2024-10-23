#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <sys/time.h>
#include <math.h>

#include "sorting.h"

// Функция для заполнения массива по возрастанию
void fillArrayAscending(uint32_t arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;  // Заполняем массив числами от 1 до n
    }
}

// Функция для заполнения массива по убыванию
void fillArrayDescending(uint32_t arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;  // Заполняем массив числами от n до 1
    }
}

// Функция для заполнения массива случайными числами в диапазоне [min, max)
void fillArrayRandom(uint32_t arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;  // Генерируем случайное число
    }
}

// Функция для измерения времени выполнения в секундах
double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;  // Возвращаем текущее время в секундах
}

// Функция для запуска тестов сортировки и записи результатов в файл
void runTests(const char *filename, void (*fillArrayFunc)(uint32_t[], int, int, int), int min, int max) {
    FILE *f = fopen(filename, "w");  // Открываем файл для записи
    if (f == NULL) {
        printf("Error opening file %s!\n", filename);
        return;  // Если не удалось открыть файл, выводим ошибку и возвращаемся
    }

    fprintf(f, "Elements\tBubbleSort\tQuickSort\n");  // Записываем заголовок таблицы в файл
    for (int n = pow(2, 8); n <= pow(2, 15); n = n + 127) {  // Проходим по различным размерам массивов
        uint32_t *arr_bubble = malloc(n * sizeof(uint32_t));  // Выделяем память для массива bubble sort
        uint32_t *arr_quick = malloc(n * sizeof(uint32_t));  // Выделяем память для массива quick sort

        double tBubble, tQuick;

        // Заполняем массивы
        fillArrayFunc(arr_bubble, n, min, max);
        fillArrayFunc(arr_quick, n, min, max);

        // Измеряем время выполнения пузырьковой сортировки
        double start_time = wtime();
        bubbleSort(arr_bubble, n);
        tBubble = wtime() - start_time;

        // Измеряем время выполнения быстрой сортировки
        start_time = wtime();
        quickSort(arr_quick, 0, n - 1);
        tQuick = wtime() - start_time;

        // Записываем результаты в файл
        fprintf(f, "%d\t\t%f\t%f\n", n, tBubble, tQuick);

        // Освобождаем выделенную память
        free(arr_bubble);
        free(arr_quick);
    }

    fclose(f);  // Закрываем файл
}

int main() {
    // Тест на случайных данных
    runTests("resrand.txt", fillArrayRandom, 0, pow(2, 15));

    // Тест на возрастающих данных
    runTests("resup.txt", (void(*)(uint32_t[], int, int, int))fillArrayAscending, 0, 0);

    // Тест на убывающих данных
    runTests("resdown.txt", (void(*)(uint32_t[], int, int, int))fillArrayDescending, 0, 0);

    return 0;
}
