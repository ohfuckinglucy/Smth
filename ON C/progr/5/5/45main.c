// Эта программа на языке C подсчитывает количество положительных элементов массива A, 
// которые следуют сразу за отрицательными элементами.

#include <stdio.h>

int countPosAfterNeg(int A[], int n) {
    int i, s = 0;
    for (i = 1; i < n; i++) {
        if (A[i] > 0 && A[i - 1] < 0) {
            s++;
        }
    }
    return s;
}

int main() {
    int A[] = {1, -2, 3, -4, 5, -6, 7, 8, -9, 10}; // Пример массива
    int n = sizeof(A) / sizeof(A[0]);
    int result = countPosAfterNeg(A, n);

    printf("Число положительных элементов следующих за отрицательными: %d\n", result);

    return 0;
}
