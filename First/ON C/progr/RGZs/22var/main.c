#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <key> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    // Получаем ключ из аргументов командной строки
    char *key = argv[1];
    int key_len = strlen(key);

    // Читаем текст из входного файла
    char *text = NULL;
    read_file_content(argv[2], &text);

    // Удаляем символ новой строки в конце, если он есть
    text[strcspn(text, "\n")] = '\0';
    int text_len = strlen(text);

    // Подсчет количества строк
    int rows = (text_len + key_len - 1) / key_len;

    // Создание таблицы для шифрования
    char **arr = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        arr[i] = (char *)malloc(key_len * sizeof(char));
        memset(arr[i], '\0', key_len * sizeof(char));
    }

    for (int i = 0, k = 0; i < rows; i++) {
        for (int j = 0; j < key_len && k < text_len; j++, k++) {
            arr[i][j] = text[k];
        }
    }

    // Сохраняем оригинальные индексы
    int *original_index = (int *)malloc(key_len * sizeof(int));
    for (int i = 0; i < key_len; i++) {
        original_index[i] = i;
    }

    // Сортировка столбцов по ключу
    sort_columns(key, key_len, rows, arr, original_index);

    // Формируем зашифрованный текст
    char *encrypted_text = (char *)malloc((rows * key_len + 1) * sizeof(char));
    int index = 0;
    for (int j = 0; j < key_len; j++) {
        for (int i = 0; i < rows; i++) {
            if (arr[i][j] != '\0') {
                encrypted_text[index++] = arr[i][j];
            }
        }
    }
    encrypted_text[index] = '\0';

    // Записываем зашифрованный текст в выходной файл
    FILE *output_file = fopen(argv[3], "w");
    if (!output_file) {
        perror("Ошибка при открытии файла для записи");
        return 1;
    }
    fprintf(output_file, "%s", encrypted_text);
    fclose(output_file);

    // Вывод изначального текста, зашифрованного и дешифрованного текста
    printf("Изначальный текст: %s\n", text);
    printf("Зашифрованный текст: %s\n", encrypted_text);

    // Дешифровка текста
    decrypt_columns(key, key_len, rows, arr, original_index);

    // Формируем расшифрованный текст
    char *decrypted_text = (char *)malloc((rows * key_len + 1) * sizeof(char));
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key_len; j++) {
            if (arr[i][j] != '\0') {
                decrypted_text[index++] = arr[i][j];
            }
        }
    }
    decrypted_text[index] = '\0';

    printf("Расшифрованный текст: %s\n", decrypted_text);

    // Освобождение памяти
    free(text);
    free(encrypted_text);
    free(decrypted_text);
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
    free(original_index);

    return 0;
}
