#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"

void read_file_content(const char *filename, char **content) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка при открытии файла");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    *content = (char *)malloc(length + 1);
    if (*content) {
        size_t total_read = 0;
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file)) {
            total_read += strlen(buffer);
            *content = (char *)realloc(*content, total_read + 1);
            strcat(*content, buffer);
        }
    }
    fclose(file);

    // Удаляем символы новой строки и заменяем их пробелами
    char *p = *content;
    while (*p) {
        if (*p == '\n') {
            *p = ' ';
        }
        p++;
    }
}

// Функция для сортировки столбцов
void sort_columns(char *key, int key_len, int rows, char **arr, int *original_index) {
    for (int i = 0; i < key_len - 1; i++) {
        for (int j = i + 1; j < key_len; j++) {
            if (key[i] > key[j]) {
                // Меняем столбцы местами
                for (int k = 0; k < rows; k++) {
                    char temp = arr[k][i];
                    arr[k][i] = arr[k][j];
                    arr[k][j] = temp;
                }
                // Меняем символы ключа местами
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

// Функция для расшифровки столбцов
void decrypt_columns(char *key, int key_len, int rows, char **arr, int *original_index) {
    char **temp_arr = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        temp_arr[i] = (char *)malloc(key_len * sizeof(char));
    }

    // Копируем содержимое arr в temp_arr согласно оригинальным индексам
    for (int j = 0; j < key_len; j++) {
        for (int i = 0; i < rows; i++) {
            temp_arr[i][original_index[j]] = arr[i][j];
        }
    }

    // Копируем обратно в arr
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key_len; j++) {
            arr[i][j] = temp_arr[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        free(temp_arr[i]);
    }
    free(temp_arr);
}
