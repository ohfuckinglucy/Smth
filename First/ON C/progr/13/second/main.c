#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

int main() {
    int nValues[] = {10};
    int nCount = sizeof(nValues) / sizeof(nValues[0]);

    int fillType;
    printf("Выберите тип заполнения массива:\n");
    printf("1. Ввод с клавиатуры\n");
    printf("2. Случайные числа\n");
    printf("3. Из файла\n");
    scanf("%d", &fillType);

    printf("\nМетод сортировки | n | C (сравнения) | M (пересылки)\n");

    for (int i = 0; i < nCount; i++) {
        int n = nValues[i];
        int arr[n];

        fillArray(arr, n, fillType);

        int comparisonsShell = 0, swapsShell = 0;
        int comparisonsInsertion = 0, swapsInsertion = 0;
        int comparisonsBubble = 0, swapsBubble = 0;
        int comparisonsCounting = 0, swapsCounting = 0;

        int arrShell[n], arrInsertion[n], arrBubble[n], arrCounting[n];

        // Копирование массива для каждого метода сортировки
        for (int j = 0; j < n; j++) {
            arrShell[j] = arr[j];
            arrInsertion[j] = arr[j];
            arrBubble[j] = arr[j];
            arrCounting[j] = arr[j];
        }

        // Сортировка методом Шелла
        shellSort(arrShell, n, &comparisonsShell, &swapsShell);

        // Сортировка методом простого включения
        insertionSort(arrInsertion, n, &comparisonsInsertion, &swapsInsertion);

        // Сортировка методом пузырьковой сортировки
        bubbleSort(arrBubble, n, &comparisonsBubble, &swapsBubble);

        // Сортировка методом сортировки подсчетом
        countingSort(arrCounting, n, &comparisonsCounting, &swapsCounting);

        printf("Шелла              | %d | %10d | %11d\n", n, comparisonsShell, swapsShell);
        printf("Простого включения | %d | %10d | %11d\n", n, comparisonsInsertion, swapsInsertion);
        printf("Пузырьковая        | %d | %10d | %11d\n", n, comparisonsBubble, swapsBubble);
        printf("Подсчетом          | %d | %10d | %11d\n", n, comparisonsCounting, swapsCounting);

        printf("\n");
    }

    return 0;
}
