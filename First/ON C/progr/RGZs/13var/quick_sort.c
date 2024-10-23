#include "sorting.h"

// Функция для обмена значений переменных
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Функция для разделения массива и возврата индекса опорного элемента
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // выбираем последний элемент как опорный
    int i = (low - 1); // индекс меньшего элемента

    for (int j = low; j <= high - 1; j++) {
        // если текущий элемент меньше или равен опорному
        if (arr[j] <= pivot) {
            i++; // увеличиваем индекс меньшего элемента
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Основная функция быстрой сортировки, рекурсивно сортирующая подмассивы
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi - индекс опорного элемента
        int pi = partition(arr, low, high);

        // Рекурсивно сортируем элементы до и после опорного
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
