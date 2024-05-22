#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Функция для чтения текста из файла
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла для чтения");
        exit(EXIT_FAILURE);
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* buffer = malloc(length + 1);
    if (!buffer) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    
    fclose(file);
    return buffer;
}

// Функция для записи текста в файл
void write_file(const char* filename, const char* text) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка открытия файла для записи");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%s", text);
    fclose(file);
}

// Функция для вычисления размеров таблицы
void calculate_table_size(int length, int* rows, int* cols) {
    *rows = 4; // Начальное значение
    *cols = (length + *rows - 1) / *rows; // Округление вверх
    while (*rows * *cols < length) {
        (*rows)++;
        *cols = (length + *rows - 1) / *rows;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* input_filename = argv[1];
    const char* output_filename = argv[2];

    // Чтение исходного текста из файла
    char* text = read_file(input_filename);
    printf("Исходный текст: %s\n", text);

    // Вычисление необходимых размеров таблицы
    int length = strlen(text);
    int rows, cols;
    calculate_table_size(length, &rows, &cols);
    
    // Вывод размера таблицы (для сверки работоспособности).

    // printf("Размер таблицы: %d x %d\n", rows, cols);
    
    // Шифрование текста
    char* encrypted = encrypt(text, rows, cols);
    printf("Зашифрованный текст: %s\n", encrypted);

    // Запись зашифрованного текста в файл
    write_file(output_filename, encrypted);
    
    // Дешифрование текста
    char* decrypted = decrypt(encrypted, rows, cols);
    printf("Дешифрованный текст: %s\n", decrypted);
    
    // Проверка совпадения исходного и дешифрованного текста
    if (strcmp(text, decrypted) == 0) {
        printf("Успешное дешифрование!\n");
    } else {
        printf("Ошибка дешифрования.\n");
    }
    
    // Освобождение памяти
    free_memory(text);
    free_memory(encrypted);
    free_memory(decrypted);
    
    return 0;
}
