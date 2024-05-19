#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Функция для поиска минимального элемента среди отрицательных чисел
int findMinNegative(int *arr, int n) {
    // Базовый случай: если массив пуст, возвращаем максимально возможное значение
    if (n == 0) {
        return INT_MAX;
    }
    
    // Рекурсивный случай: ищем минимальный элемент в оставшейся части массива
    int minInRest = findMinNegative(arr, n - 1);
    
    // Если текущий элемент отрицательный и меньше найденного ранее минимального отрицательного
    if (arr[n - 1] < 0 && arr[n - 1] < minInRest) {
        return arr[n - 1];
    }
    
    return minInRest;
}

int main() {
    int n;
    
    // Чтение размера массива
    printf("Введите размер массива: ");
    scanf("%d", &n);
    
    // Выделение памяти под массив
    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    
    // Чтение элементов массива
    printf("Введите элементы массива:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Поиск минимального отрицательного элемента
    int minNegative = findMinNegative(arr, n);
    
    // Проверка результата
    if (minNegative == INT_MAX) {
        printf("В массиве нет отрицательных чисел.\n");
    } else {
        printf("Минимальное отрицательное число: %d\n", minNegative);
    }
    
    // Освобождение выделенной памяти
    free(arr);
    
    return 0;
}
