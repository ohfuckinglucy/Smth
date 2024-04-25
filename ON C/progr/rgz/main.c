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
        printf("Ошибка чтения файла.\n");
        fclose(input_file);
        return 1;
    }

    // Получаем размер входного файла
    fseek(input_file, 0, SEEK_END); // функция для перемещения указателя в какую-то часть файла (в данном случае в конец).
    long input_file_size = ftell(input_file); // функция для сообщения где находится указатель (в данный момент возвращает размер файла).
    rewind(input_file); // возвращает указатель в начало файла.

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

    srand(1234); // Используем статическое зерно для воспроизводимости

    char *key = (char *)malloc(input_file_size * sizeof(char));

    if (key == NULL) {
        printf("Выделение памяти провалено.\n");
        fclose(input_file);
        fclose(output_file);
        free(text);
        return 1;
    }
    for (int i = 0; i < input_file_size; ++i) {
        key[i] = rand() % 256; // Случайные значения от 0 до 255
    }

    // Шифруем текст
    encrypt_decrypt(text, key, input_file_size, input_file_size);

    // Записываем зашифрованный текст в выходной файл
    fwrite(text, sizeof(char), input_file_size, output_file);

    // Дешифруем текст
    encrypt_decrypt(text, key, input_file_size, input_file_size);
    // Раскомментируйте чтобы увидеть расшифрованный текст.


    printf("Шифрованный текст:\n%s\n", text);

    // Освобождаем выделенную память и закрываем файлы
    fclose(input_file);
    fclose(output_file);
    free(text);
    free(key);

    return 0;
}
