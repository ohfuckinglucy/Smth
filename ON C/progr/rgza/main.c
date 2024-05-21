#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Введите: %s <Файл ключа> <Входной файл> <Выходной файл>\n", argv[0]);
        return 1;
    }

    // Открываем файл ключа
    FILE *key_file = fopen(argv[1], "r");
    if (!key_file) {
        perror("Ошибка при открытии файла ключа");
        return 1;
    }

    // Читаем ключ из файла
    char *key = NULL;
    size_t key_len = 0;
    if (getline(&key, &key_len, key_file) == -1) {
        perror("Ошибка при чтении файла ключа");
        fclose(key_file);
        if (key) free(key);
        return 1;
    }
    fclose(key_file);

    // Удаляем символ новой строки, если он есть
    key[strcspn(key, "\n")] = '\0';
    key_len = strlen(key);

    // Открываем файл текста
    FILE *text_file = fopen(argv[2], "r");
    if (!text_file) {
        perror("Ошибка при открытии файла текста");
        free(key);
        return 1;
    }

    // Определяем размер файла текста
    fseek(text_file, 0, SEEK_END);
    size_t text_len = ftell(text_file);
    fseek(text_file, 0, SEEK_SET);

    // Выделяем память и читаем весь файл текста
    char *text = (char *)malloc(text_len + 1);
    if (!text) {
        perror("Ошибка при выделении памяти");
        fclose(text_file);
        free(key);
        return 1;
    }
    fread(text, 1, text_len, text_file);
    text[text_len] = '\0'; // Добавляем нулевой символ в конец строки
    fclose(text_file);

    // Удаляем все символы новой строки
    char *p = text;
    char *q = text;
    while (*q) {
        if (*q != '\n' && *q != '\r') {
            *p++ = *q;
        }
        q++;
    }
    *p = '\0';
    text_len = strlen(text);

    // Подсчет количества строк
    int rows = (text_len + key_len - 1) / key_len;

    // Создание таблицы для шифрования
    char **arr = (char **)malloc(rows * sizeof(char *));
    if (!arr) {
        perror("Ошибка при выделении памяти");
        free(key);
        free(text);
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        arr[i] = (char *)malloc(key_len * sizeof(char));
        if (!arr[i]) {
            perror("Ошибка при выделении памяти");
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            free(key);
            free(text);
            return 1;
        }
        memset(arr[i], '\0', key_len * sizeof(char));
    }

    for (int i = 0, k = 0; i < rows; i++) {
        for (int j = 0; j < key_len && k < text_len; j++, k++) {
            arr[i][j] = text[k];
        }
    }

    // Сохраняем оригинальные индексы
    int *original_index = (int *)malloc(key_len * sizeof(int));
    if (!original_index) {
        perror("Ошибка при выделении памяти");
        for (int i = 0; i < rows; i++) {
            free(arr[i]);
        }
        free(arr);
        free(key);
        free(text);
        return 1;
    }
    for (int i = 0; i < key_len; i++) {
        original_index[i] = i;
    }

    // Сортировка столбцов по ключу
    sortingcol(key, key_len, rows, arr, original_index);

    // Открываем файл для записи шифрованного текста
    FILE *output_file = fopen(argv[3], "w");
    if (!output_file) {
        perror("Ошибка при открытии файла для шифрованного текста");
        for (int i = 0; i < rows; i++) {
            free(arr[i]);
        }
        free(arr);
        free(original_index);
        free(key);
        free(text);
        return 1;
    }

    // Записываем шифрованный текст в файл
    for (int j = 0; j < key_len; j++) {
        for (int i = 0; i < rows; i++) {
            if (arr[i][j] != '\0') {
                fputc(arr[i][j], output_file);
            }
        }
    }
    fclose(output_file);

    // Вывод шифрованного текста на экран
    printf("Шифрованный текст: ");
    for (int j = 0; j < key_len; j++) {
        for (int i = 0; i < rows; i++) {
            if (arr[i][j] != '\0') {
                printf("%c", arr[i][j]);
            }
        }
    }
    printf("\n");

    // Дешифровка текста
    decrypt(key, key_len, rows, arr, original_index);

    // Вывод расшифрованного текста
    printf("Расшифрованный текст: ");
    char *decrypted_text = (char *)malloc(text_len + 1);
    if (!decrypted_text) {
        perror("Ошибка при выделении памяти");
        for (int i = 0; i < rows; i++) {
            free(arr[i]);
        }
        free(arr);
        free(original_index);
        free(key);
        free(text);
        return 1;
    }
    p = decrypted_text;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key_len; j++) {
            if (arr[i][j] != '\0') {
                printf("%c", arr[i][j]);
                *p++ = arr[i][j];
            }
        }
    }
    *p = '\0';
    printf("\n");

    // Проверка совпадения текста
    if (strcmp(text, decrypted_text) == 0) {
        printf("Расшифрованный текст совпадает с исходным текстом.\n");
    } else {
        printf("Расшифрованный текст не совпадает с исходным текстом.\n");
    }

    // Освобождение памяти
    free(key);
    free(text);
    free(decrypted_text);
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
    free(original_index);

    return 0;
}
