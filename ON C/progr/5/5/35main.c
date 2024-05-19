// Эта программа реализует алгоритм сортировки выбором. 
// Она находит наименьший элемент в массиве и перемещает его в конец массива. 
// Затем уменьшает размер массива и повторяет процесс до тех пор, пока размер массива не станет нулевым.

#include <stdio.h>

void selectionSortToEnd(int A[], int n) {
    int i, k, c;
    while (n != 0) {
        for (k = 0, i = 1; i < n; i++) {
            if (A[i] < A[k]) k = i;
        }
        c = A[k];
        A[k] = A[n - 1];
        A[n - 1] = c;
        n--;
    }
}

int main() {
    int A[] = {2, 76, 14, 3, 11}; // Пример массива
    int n = sizeof(A) / sizeof(A[0]);
    int i;

    printf("Исходный массив:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    selectionSortToEnd(A, n);

    printf("Массив после сортировки:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
