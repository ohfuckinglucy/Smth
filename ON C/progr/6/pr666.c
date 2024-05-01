#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int m, p = 0, r = 0;
    printf("Задайте длину массива Z: ");
    scanf("%d", &m);

    int z[m];
    for (int i = 0; i < m; i++) {
        z[i] = i + 4;
    }

    int max = z[m - 1];
    for (int i = 0; i < m; i++) {
        if (z[i] > max) {
            max = z[i];
        }
    }

    printf("Максимальный элемент массива: %d\n", max);
    
    for (int i = 0; i < m; i++) {
        if (z[i] == max) {
            z[i] = 0;
        }
        printf("%d\n", z[i]);
    }

    for (int i = 0; i < m; i++) {
        p += z[i];
        if (z[i] != 0) {
            r += 1;
        }
    }

    if (r > 0) {
        printf("Среднее арифметическое положительных элементов: %d\n", p / r);
    } else {
        printf("В массиве нет положительных элементов.\n");
    }

    // Сортировка по убыванию модулей
    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            if (abs(z[i]) < abs(z[j])) {
                int temp = z[i];
                z[i] = z[j];
                z[j] = temp;
            }
        }
    }

    printf("Массив после сортировки по убыванию модулей:\n");
    for (int i = 0; i < m; i++) {
        printf("%d\n", z[i]);
    }

    return 0;
}
