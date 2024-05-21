#include <stdio.h>
#include <stdlib.h>

// Сравнение для функции qsort (обратный порядок)
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); // Обратное сравнение
}

int main() {
    // Открываем файл для записи
    FILE *file = fopen("output.txt", "w");

    // Пишем числа от 1 до 500 в файл
    for (int i = 1; i <= 500; ++i) {
        fprintf(file, "%d\n", i);
    }

    // Закрываем файл
    fclose(file);

    // Открываем файл для считывания
    file = fopen("output.txt", "r");

    // Подготавливаем массив для считывания чисел
    int numbers[500];

    // Считываем числа из файла в массив
    for (int i = 0; i < 500; ++i) {
        fscanf(file, "%d", &numbers[i]);
    }

    // Закрываем файл
    fclose(file);

    // Сортируем массив в обратном порядке
    qsort(numbers, 500, sizeof(int), compare);

    // Открываем файл для записи отсортированных чисел в обратном порядке
    file = fopen("sorted_output.txt", "w");

    // Записываем отсортированные числа в файл
    for (int i = 0; i < 500; ++i) {
        fprintf(file, "%d ", numbers[i]);
    }

    // Закрываем файл
    fclose(file);

    return 0;
}
