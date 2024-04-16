#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

void shellSort(int arr[], int n, int* comparisons, int* swaps) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                (*comparisons)++;
                swap(&arr[j], &arr[j - gap], swaps);
            }
            (*comparisons)++;
            arr[j] = temp;
        }
    }
}

void insertionSort(int arr[], int n, int* comparisons, int* swaps) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            swap(&arr[j + 1], &arr[j], swaps);
            j--;
        }
        (*comparisons)++;
        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n, int* comparisons, int* swaps) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1], swaps);
            }
        }
    }
}

void countingSort(int arr[], int n, int* comparisons, int* swaps) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        (*comparisons)++;
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int countSize = max + 1;
    int* count = (int*)malloc(countSize * sizeof(int));
    int* output = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < countSize; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
        (*swaps)++;
    }

    for (int i = 1; i < countSize; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
        (*swaps)++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}