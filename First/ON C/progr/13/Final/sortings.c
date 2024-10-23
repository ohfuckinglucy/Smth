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
void CountingSort(int arr[], int n, int *comparisons, int *swaps) {
    if (n <= 0) {
        return;
    }

    int max_value = arr[0];
    for (int i = 1; i < n - 1; ++i) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    int count[max_value + 1];

    for (int i = 0; i <= max_value; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        ++count[arr[i]];
    }

    for (int i = 1; i <= max_value; ++i) {
        count[i] += count[i - 1];
    }

    int output[n];

    for (int i = n - 1; i >= 0; --i) {
        (*comparisons)++;
        output[count[arr[i]] - 1] = arr[i];
        (*swaps)++;
        --count[arr[i]];
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
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

