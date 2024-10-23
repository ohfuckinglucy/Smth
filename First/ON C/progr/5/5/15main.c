// Эта программа на языке C удаляет простые числа из массива A длиной n

#include <stdio.h>

// Функция для удаления простых чисел из массива
void removePrimes(int A[], int *n) {
    int i, m, j;
    for (i = 0; i < *n; i++) {
        for (m = 2; m < A[i]; m++) {
            if (A[i] % m == 0) break;
        }
        if (m == A[i]) {
            for (j = i; j < *n - 1; j++) {
                A[j] = A[j + 1];
            }
            (*n)--;
            i--;
        }
    }
}

int main() {
    int A[] = {3, 4, 5, 6, 7, 8, 9, 10}; // Пример массива
    int n = sizeof(A) / sizeof(A[0]);
    int i;

    printf("Исходные массив:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    removePrimes(A, &n);

    printf("Массив после удаления простых чисел:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}