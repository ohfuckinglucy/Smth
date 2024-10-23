// Эта программа на языке C выполняет циклический сдвиг массива A на один элемент влево. 

#include <stdio.h>

void shiftLeft(int A[], int n) {
    int s = A[0]; // Сохраняем первый элемент массива
    int i;
    for (i = 1; i < n; i++) {
        A[i - 1] = A[i]; // Сдвигаем каждый элемент влево
    }
    A[n - 1] = s; // Помещаем первый элемент в конец массива
}

int main() {
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Пример массива
    int n = sizeof(A) / sizeof(A[0]);
    int i;

    printf("Исходный массив:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    shiftLeft(A, n);

    printf("Массив после сдвига:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
