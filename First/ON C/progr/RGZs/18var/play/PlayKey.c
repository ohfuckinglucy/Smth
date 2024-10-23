#include "playheader.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h> // Для использования функции wcstombs()

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, ""); // Установка локали для корректного отображения кириллических символов

    if (argc < 4) {
        printf("Использование: %s input.txt output.txt ключ\n", argv[0]);
        return 1;
    }

    wchar_t key[MAX_TEXT_SIZE];
    mbstowcs(key, argv[3], MAX_TEXT_SIZE); // Преобразование ключа из строки в широкие символы

    wchar_t inputText[MAX_TEXT_SIZE] = {0};
    wchar_t encodedText[MAX_TEXT_SIZE] = {0};
    wchar_t table[TABLE_ROWS][TABLE_COLUMNS];

    // Открытие файла для чтения
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Ошибка при открытии файла для чтения.\n");
        return 1;
    }

    // Чтение текста из файла
    fgetws(inputText, MAX_TEXT_SIZE, inputFile);
    fclose(inputFile);

    // Удаление дубликатов из ключа
    removeDuplicates(key);

    // Генерация таблицы шифрования
    generateTable(key, table, RU_ALPHABET_SIZE);

    // Шифрование текста
    encryptText(inputText, encodedText, key);

    // Открытие файла для записи
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("Ошибка при открытии файла для записи.\n");
        return 1;
    }

    // Запись зашифрованного текста в файл
    fwprintf(outputFile, L"%ls", encodedText);
    fclose(outputFile);

    printf("Текст успешно зашифрован и сохранен в файле %s.\n", argv[2]);

    return 0;
}
