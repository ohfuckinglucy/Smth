#include <stdlib.h>
#include <stdio.h>
#include "header.h"
#include <time.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

int comparisonsShell = 0, swapsShell = 0;
int comparisonsInsertion = 0, swapsInsertion = 0;
int comparisonsBubble = 0, swapsBubble = 0;
int comparisonsCounting = 0, swapsCounting = 0;


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Функция для бинарного поиска места вставки элемента
int binarySearch(int a[], int item, int low, int high, int *comparisons) {
    if (high <= low) {
        (*comparisons)++;
        return (item > a[low]) ? (low + 1) : low;
    }

    int mid = (low + high) / 2;
    (*comparisons)++;
    if (item == a[mid]) {
        return mid + 1;
    }

    (*comparisons)++;
    if (item > a[mid]) {
        return binarySearch(a, item, mid + 1, high, comparisons);
    }
    return binarySearch(a, item, low, mid - 1, comparisons);
}

// Функция для сортировки вставками с использованием бинарного поиска
void BinaryInsertionSort(int a[], int n, int *comparisons, int *swaps) {
    for (int i = 1; i < n; i++) {
        int selected = a[i];
        int j = i - 1;

        // Найти место вставки для selected элемента с использованием бинарного поиска
        int loc = binarySearch(a, selected, 0, j, comparisons);

        // Перемещение всех элементов вправо для освобождения места для вставки
        while (j >= loc) {
            (*comparisons)++;
            a[j + 1] = a[j];
            (*swaps)++;
            j--;
        }
        a[j + 1] = selected;
    }
}

void insertionSort(int arr[], int n, int *comparisons, int *swaps) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            (*swaps)++;
            j = j - 1;
        }
        (*comparisons)++;  // Последнее сравнение, когда условие не выполняется
        arr[j + 1] = key;
        (*swaps)++;  // Пересылка для вставки key
    }
}


void ShellSort(int a[], int n, int *comparisons, int *swaps) {
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= interval && a[j - interval] > temp; j -= interval) {
                (*comparisons)++;
                a[j] = a[j - interval];
                (*swaps)++;
            }
            a[j] = temp;
            if (j != i) {
                (*swaps)++;
            }
        }
    }
}


// void generateDecreasingArray(int arr[], int n) {
//     for (int i = 0; i < n; i++) {
//         arr[i] = n - i;
//     }
// }

// void generateRandomArray(int arr[], int n) {
//     srand(time(NULL));
//     for (int i = 0; i < n; i++) {
//         arr[i] = rand() % 100;
//     }
// }

// void generateIncreasingArray(int arr[], int n) {
//     for (int i = 0; i < n; i++) {
//         arr[i] = i + 1;
//     }
// }