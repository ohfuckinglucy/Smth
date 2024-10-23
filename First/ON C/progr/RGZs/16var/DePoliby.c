#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "header.h"

#define MAX_SIZE 10000

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc != 3 && argc != 4) {
        wprintf(L"Использование: %s <входной файл> <выходной файл> [Исходный файл]\n", argv[0]);
        return 1;
    }

    FILE *encryptedFile = fopen(argv[1], "r");
    FILE *decryptedFile = fopen(argv[2], "w");

    if (encryptedFile == NULL) {
        wprintf(L"Ошибка открытия файла %s\n", argv[1]);
        return 1;
    }

    if (decryptedFile == NULL) {
        wprintf(L"Ошибка открытия файла %s\n", argv[2]);
        fclose(encryptedFile);
        return 1;
    }

    wchar_t *ciphertext = (wchar_t *)malloc(MAX_SIZE * sizeof(wchar_t));
    wchar_t *plaintext = (wchar_t *)malloc(2 * MAX_SIZE * sizeof(wchar_t));

    if (ciphertext == NULL || plaintext == NULL) {
        wprintf(L"Ошибка выделения памяти\n");
        fclose(encryptedFile);
        fclose(decryptedFile);
        free(ciphertext);
        free(plaintext);
        return 1;
    }

    if (fgetws(ciphertext, MAX_SIZE, encryptedFile) == NULL) {
        wprintf(L"Ошибка чтения файла\n");
        fclose(encryptedFile);
        fclose(decryptedFile);
        free(ciphertext);
        free(plaintext);
        return 1;
    }

    fclose(encryptedFile);

    cleanText(ciphertext);

    wprintf(L"Прочитанный зашифрованный текст: %ls\n", ciphertext);

    decrypt(ciphertext, plaintext);

    wprintf(L"Расшифрованный текст: %ls\n", plaintext);

    fputws(plaintext, decryptedFile);

    if (argc == 4) {
    FILE *sourceFile = fopen(argv[3], "r");
    if (sourceFile == NULL) {
        wprintf(L"Ошибка открытия файла %s\n", argv[3]);
        fclose(decryptedFile);
        free(ciphertext);
        free(plaintext);
        return 1;
    }

    wchar_t *sourceText = (wchar_t *)malloc(MAX_SIZE * sizeof(wchar_t));
    if (sourceText == NULL) {
        wprintf(L"Ошибка выделения памяти\n");
        fclose(sourceFile);
        fclose(decryptedFile);
        free(ciphertext);
        free(plaintext);
        return 1;
    }

    if (fgetws(sourceText, MAX_SIZE, sourceFile) == NULL) {
        wprintf(L"Ошибка чтения файла\n");
        fclose(sourceFile);
        fclose(decryptedFile);
        free(sourceText);
        free(ciphertext);
        free(plaintext);
        return 1;
    }

    fclose(sourceFile);

    cleanText(sourceText);

    if (wcscmp(plaintext, sourceText) == 0) {
        wprintf(L"Содержимое расшифрованного текста совпадает с содержимым исходного файла.\n");
    } else {
        wprintf(L"Содержимое расшифрованного текста не совпадает с содержимым исходного файла.\n");
        wprintf(L"Расшифрованный текст: %ls\n", plaintext);
        wprintf(L"Исходный текст: %ls\n", sourceText);
    }

    free(sourceText);
}


    fclose(decryptedFile);

    free(ciphertext);
    free(plaintext);

    return 0;
}