#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    // Открываем входной файл для чтения
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Ошибка чтения файла.\n");
        return 1;
    }

    // Открываем выходной файл для записи
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        printf("Ошибка открытия файла для записи.\n");
        fclose(input_file);
        return 1;
    }

    // Получаем размер входного файла
    fseek(input_file, 0, SEEK_END);
    long input_file_size = ftell(input_file);
    rewind(input_file);

    // Выделяем память под буфер для хранения текста
    char *text = (char *)malloc(input_file_size * sizeof(char));
    if (text == NULL) {
        printf("Выделение памяти провалено.\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    // Считываем текст из входного файла
    fread(text, sizeof(char), input_file_size, input_file);

    // Сохраняем исходный текст для последующего сравнения
    char *original_text = (char *)malloc(input_file_size * sizeof(char));
    if (original_text == NULL) {
        printf("Выделение памяти провалено.\n");
        fclose(input_file);
        fclose(output_file);
        free(text);
        return 1;
    }
    memcpy(original_text, text, input_file_size);

    srand(1234); // Используем статическое зерно для воспроизводимости

    char *key = (char *)malloc(input_file_size * sizeof(char));
    if (key == NULL) {
        printf("Выделение памяти провалено.\n");
        fclose(input_file);
        fclose(output_file);
        free(text);
        free(original_text);
        return 1;
    }

    // Генерируем случайный ключ
    for (int i = 0; i < input_file_size; ++i) {
        key[i] = rand() % 256; // Случайные значения от 0 до 255
    }

    // Шифруем текст
    encrypt_decrypt(text, key, input_file_size, input_file_size);

    // Записываем зашифрованный текст в выходной файл
    fwrite(text, sizeof(char), input_file_size, output_file);

    printf("Зашифрованный текст:\n%s\n\n", text);

    // Дешифруем текст
    encrypt_decrypt(text, key, input_file_size, input_file_size);

    printf("Дешифрованный текст:\n%s\n\n", text);

    // Проверяем, совпадает ли дешифрованный текст с исходным
    if (memcmp(original_text, text, input_file_size) == 0) {
        printf("Дешифрованный текст совпадает с исходным.\n");
    } else {
        printf("Дешифрованный текст не совпадает с исходным.\n");
    }

    // Освобождаем выделенную память и закрываем файлы
    fclose(input_file);
    fclose(output_file);
    free(text);
    free(original_text);
    free(key);

    return 0;
}
