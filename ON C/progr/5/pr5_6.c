#include <stdio.h>
// поиск индекса и значения дубликатов в массиве чисел
int megai[10];

int findDuplicate(int c[], int n) {
    int i, j;
    int A[10];
    int found = 0;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (c[i] == c[j]) {
                A[i] = c[i];
                megai[i] = i;
                found = 1;
            }
        }
    }

    if (found) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 2, 3, 9};
    int size = sizeof(array) / sizeof(array[0]);
    int result = findDuplicate(array, size);

    if (result == 0) {
        for (int i = 0; i < 3; i++) {
            printf("DublIndex %d, Value %d\n", megai[i], array[megai[i]]);
        }
    } else {
        printf("DublsNO\n");
    }

    return 0;
}
