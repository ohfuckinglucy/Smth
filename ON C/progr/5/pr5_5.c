#include <stdio.h>
// 11 variant
// Проверка на простое число
int main() {
    int v = 20;
    int A[100];
    int i, a, n;

    for (i = 0, a = 2; a < v; a++) {
        for (n = 2; n < a; n++) {
            if (a % n == 0)
                break;
        }

        if (n == a)
            A[i++] = a;
    }

    A[i] = 0;

    printf("Simple numbers do %d: ", v);
    for (int j = 0; A[j] != 0; j++) {
        printf("%d ", A[j]);
    }

    return 0;
}