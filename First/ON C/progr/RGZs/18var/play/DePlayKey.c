#include "playheader.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h> // Для использования функции wcstombs()
#include <wchar.h> // Для работы с широкими символами

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, ""); // Установка локали для корректного отображения кириллических символов

    if (argc < 4) {
        printf("Использование: %s input.txt output.txt key\n", argv[0]);
        return 1;
    }

    wchar_t key[MAX_TEXT_SIZE] = {0};
    wchar_t encodedText[MAX_TEXT_SIZE] = {0};
    wchar_t decryptedText[MAX_TEXT_SIZE] = {0};
    wchar_t table[TABLE_ROWS][TABLE_COLUMNS];

    // Считывание ключа из аргумента командной строки
    mbstowcs(key, argv[3], MAX_TEXT_SIZE);

    // Открытие файла для чтения зашифрованного текста
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        wprintf(L"Ошибка при открытии файла для чтения зашифрованного текста.\n");
        return 1;
    }

    // Чтение зашифрованного текста из файла
    fgetws(encodedText, MAX_TEXT_SIZE, inputFile);
    fclose(inputFile);

    // Удаление дубликатов из ключа
    removeDuplicates(key);

    // Генерация таблицы шифрования
    generateTable(key, table, RU_ALPHABET_SIZE);

    // Расшифровка текста
    decryptText(encodedText, decryptedText, key);

    // Открытие файла для записи расшифрованного текста
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        wprintf(L"Ошибка при открытии файла для записи расшифрованного текста.\n");
        return 1;
    }

    // Запись расшифрованного текста в файл
    fwprintf(outputFile, L"%ls", decryptedText);
    fclose(outputFile);

    // Проверка на совпадение с исходным текстом, если указан файл с исходным текстом для сравнения
    if (argc == 5) {
        wchar_t originalText[MAX_TEXT_SIZE] = {0};
        FILE *originalFile = fopen(argv[4], "r");
        if (originalFile == NULL) {
            wprintf(L"Ошибка при открытии файла с исходным текстом для сравнения.\n");
            return 1;
        }
        fgetws(originalText, MAX_TEXT_SIZE, originalFile);
        fclose(originalFile);

        if (wcscmp(originalText, decryptedText) == 0) {
            wprintf(L"Расшифрованный текст совпадает с исходным текстом.\n");
        } else {
            wprintf(L"Расшифрованный текст не совпадает с исходным текстом.\n");
        }
    }

    return 0;
}
