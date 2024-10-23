#include "header.h"

int main(int argc, char *argv[]) {
    // Установка локали для корректной работы с широкими символами
    setlocale(LC_ALL, "");

    if (argc != 3) {
        fwprintf(stderr, L"Usage: %s <input_filename> <output_filename>\n", argv[0]);
        return 1;
    }

    // Открытие файла для чтения
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening input file");
        fwprintf(stderr, L"File path: %s\n", argv[1]);
        return 1;
    }

    // Определение размера файла
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Динамическое выделение памяти для содержимого файла
    char *buffer = (char *)malloc((fileSize + 1) * sizeof(char));
    if (buffer == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return 1;
    }

    // Чтение содержимого файла
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    buffer[bytesRead] = '\0'; // Завершаем строку нулевым символом

    fclose(file);

    // Преобразование в широкие символы
    size_t wcharCount = mbstowcs(NULL, buffer, 0) + 1;
    wchar_t *word = (wchar_t *)malloc(wcharCount * sizeof(wchar_t));
    if (word == NULL) {
        perror("Memory allocation error");
        free(buffer);
        return 1;
    }
    mbstowcs(word, buffer, wcharCount);

    // Очистка буфера
    free(buffer);

    // Удаление символа новой строки, пробела или возврата каретки, если он есть
    wchar_t *newline = wcschr(word, L'\n');
    if (newline) *newline = L'\0';
    wchar_t *space = wcschr(word, L' ');
    if (space) *space = L'\0';
    wchar_t *carriage = wcschr(word, L'\r');
    if (carriage) *carriage = L'\0';

    // Открытие файла для записи
    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        perror("Error opening output file");
        free(word);
        return 1;
    }

    // Генерация анаграмм и вывод
    generateAnagrams(word, 0, wcslen(word) - 1, output);

    // Освобождение выделенной памяти
    free(word);
    fclose(output);

    return 0;
}
