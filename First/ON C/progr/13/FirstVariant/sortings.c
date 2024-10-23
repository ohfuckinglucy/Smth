#include <stdlib.h>
#include <stdio.h>
#include "header.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(int a[], int n, int *comparisons, int *swaps) {
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            (*comparisons)++;
            if(a[j] > a[j+1]){
                (*swaps)++;
                swap(&a[j], &a[j+1]);
            }
        }
    }
}
void CountingSort(int arr[], int n, int range, int *comparisons, int *swaps) {
    int output[n];
    int count[range+1];
    
    for (int i = 0; i <= range; ++i)
        count[i] = 0;

    for (int i = 0; i < n; ++i)
        ++count[arr[i]];

    for (int i = 1; i <= range; ++i)
        count[i] += count[i-1];

    for (int i = 0; i < n; ++i) {
        (*comparisons)++;
        output[count[arr[i]] - 1] = arr[i];
        (*swaps)++;
        --count[arr[i]];
    }

    for (int i = 0; i < n; ++i)
        arr[i] = output[i];
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
        arr[j + 1] = key;
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
        }
    }
}
void generateDecreasingArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
}

void generateIncreasingArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

