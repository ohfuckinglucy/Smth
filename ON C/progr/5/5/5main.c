// Эта программа проверяет, есть ли в массиве A положительные элементы
// Если там все положительные, то программа возвращает 1
// Если есть хоть один отрицательный, то она вернет 0

#include <stdio.h>

int checkPositiveElements(int A[], int n) {
    int i = 0;
    while (A[i] > 0) {
        i++;
        if (i == n) return 1;
    }
    return 0;
}

int main() {
    int A[] = {1, 2, 3, 4, 5}; // Пример массива, где все элементы положительные
    int n = sizeof(A) / sizeof(A[0]);
    
    if (checkPositiveElements(A, n)) {
        printf("Все элементы положительные\n");
    } else {
        printf("Не все элементы положительные\n");
    }

    int B[] = {1, -2, 3, 4, 5}; // Пример массива, где есть отрицательный элемент
    n = sizeof(B) / sizeof(B[0]);
    
    if (checkPositiveElements(B, n)) {
        printf("Все элементы положительные\n");
    } else {
        printf("Не все элементы положительные\n");
    }

    return 0;
}
