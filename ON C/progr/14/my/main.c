#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    FILE *file;
    int size;
    int *array;
    int i;

    printf("Введите кол-во элементов в массиве: ");
    if(scanf("%d", &size) == 0){
        printf("лан пока.\n");
        exit(1);
    }

    file = fopen("array.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }
    generateRandomArray(file, size);
    fclose(file);

    file = fopen("array.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }

    array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Ошибка при выделении памяти.\n");
        return 1;
    }

    for (i = 0; i < size; i++) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);

    printf("Массив целых чисел: ");
    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    int minDeviation = findMinDeviation(array, size);
    printf("Наименьшее отклонение чисел от среднего значения: %d\n", minDeviation);

    free(array);

    return 0;
}
