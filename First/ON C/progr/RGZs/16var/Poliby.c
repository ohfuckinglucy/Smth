#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "header.h"
#include <string.h>

#define MAX_SIZE 10000

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc != 3) {
        wprintf(L"Использование: %s <входной файл> <выходной файл>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r, ccs=UTF-8");
    FILE *encryptedFile = fopen(argv[2], "w, ccs=UTF-8");

    if (inputFile == NULL) {
        wprintf(L"Ошибка открытия файла %s\n", argv[1]);
        return 1;
    }

    if (encryptedFile == NULL) {
        wprintf(L"Ошибка открытия файла %s\n", argv[2]);
        fclose(inputFile);
        return 1;
    }

    // Динамическое выделение памяти для plaintext и ciphertext
    wchar_t *plaintext = (wchar_t *)malloc(MAX_SIZE * sizeof(wchar_t));
    wchar_t *ciphertext = (wchar_t *)malloc(2 * MAX_SIZE * sizeof(wchar_t));

    if (plaintext == NULL || ciphertext == NULL) {
        wprintf(L"Ошибка выделения памяти\n");
        fclose(inputFile);
        fclose(encryptedFile);
        free(plaintext);
        free(ciphertext);
        return 1;
    }

    // Считываем файл в plaintext
    if (fgetws(plaintext, MAX_SIZE, inputFile) == NULL) {
        wprintf(L"Ошибка чтения файла\n");
        fclose(inputFile);
        fclose(encryptedFile);
        free(plaintext);
        free(ciphertext);
        return 1;
    }

    // Закрываем файл с входными данными
    fclose(inputFile);

    // Убираем символ новой строки, если он есть
    if (wcschr(plaintext, L'\n'))
        *wcschr(plaintext, L'\n') = L'\0';

    // Выводим прочитанный текст
    wprintf(L"Прочитанный текст: %ls\n", plaintext);

    // Шифруем текст
    encrypt(plaintext, ciphertext);

    // Выводим зашифрованный текст
    wprintf(L"Зашифрованный текст: %ls\n", ciphertext);

    // Записываем зашифрованный текст в файл
    fputws(ciphertext, encryptedFile);

    // Закрываем файл с зашифрованными данными
    fclose(encryptedFile);

    // Освобождаем выделенную память
    free(plaintext);
    free(ciphertext);

    return 0;
}
