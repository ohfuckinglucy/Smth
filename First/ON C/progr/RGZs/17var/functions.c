#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

// Функция для изменений позиций столбцов
void sortingcol(char *key, int key_len, int rows, char **arr, int *original_index) {
    for (int i = 0; i < key_len - 1; i++) {
        for (int j = i + 1; j < key_len; j++) {
            if (key[i] > key[j]) {
                // Изменение позиций столбцов
                for (int k = 0; k < rows; k++) {
                    char temp = arr[k][i];
                    arr[k][i] = arr[k][j];
                    arr[k][j] = temp;
                }
                // Изменение позиций символов ключа
                char temp = key[i];
                key[i] = key[j];
                key[j] = temp;
                // Меняем изначальные индексы местами
                int temp_idx = original_index[i];
                original_index[i] = original_index[j];
                original_index[j] = temp_idx;
            }
        }
    }
}

// Функция для расшифровки
void decrypt(char *key, int key_len, int rows, char **arr, int *original_index) {
    // Выделяем память под временный массив
    char **temp_arr = (char **)malloc(rows * sizeof(char *));
    if (!temp_arr) {
        perror("Ошибка при выделении памяти");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        temp_arr[i] = (char *)malloc(key_len * sizeof(char));
        if (!temp_arr[i]) {
            perror("Ошибка при выделении памяти");
            exit(1);
        }
    }

    // Копируем содержимое arr в temp_arr согласно оригинальным индексам
    for (int j = 0; j < key_len; j++) {
        for (int i = 0; i < rows; i++) {
            temp_arr[i][original_index[j]] = arr[i][j];
        }
    }

    // Копируем обратно
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key_len; j++) {
            arr[i][j] = temp_arr[i][j];
        }
    }

    // Освобождаем память, выделенную под временный массив
    for (int i = 0; i < rows; i++) {
        free(temp_arr[i]);
    }
    free(temp_arr);
}
