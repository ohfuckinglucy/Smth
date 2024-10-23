#include "playheader.h"
#include <stdio.h>
#include <stdbool.h>
#include <wchar.h>
#include <wctype.h>

// Функция для печати таблицы шифрования
void printTable(wchar_t table[][TABLE_COLUMNS], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            wprintf(L"%lc ", table[i][j]);
        }
        wprintf(L"\n");
    }
}

// Функция для удаления дубликатов из ключа
void removeDuplicates(wchar_t key[]) {
    int len = wcslen(key);
    int currentIndex = 0;

    for (int i = 0; i < len; i++) {
        if (key[i] != L' ') { // Игнорируем пробелы
            int j;
            for (j = 0; j < currentIndex; j++) {
                if (key[i] == key[j]) {
                    break;
                }
            }
            if (j == currentIndex) {
                key[currentIndex++] = key[i];
            }
        }
    }
    key[currentIndex] = L'\0';
}

// Функция для генерации таблицы шифрования на основе ключа
void generateTable(wchar_t key[], wchar_t table[][TABLE_COLUMNS], int alphabetSize) {
    int keyLength = wcslen(key);
    int i = 0;

    // Заполняем таблицу ключевыми символами
    for (i = 0; i < keyLength; i++) {
        table[i / TABLE_COLUMNS][i % TABLE_COLUMNS] = key[i];
    }

    // Заполняем оставшуюся часть таблицы символами алфавита
    wchar_t currentChar = (alphabetSize == RU_ALPHABET_SIZE) ? L'А' : L'А'; // Начинаем с кириллической буквы "А"
    for (; i < TABLE_ROWS * TABLE_COLUMNS; i++) {
        while (wcschr(key, currentChar) != NULL || currentChar == L' ') { // Пропускаем символы из ключа и пробел
                    currentChar++;
            if (currentChar == L'Ё' && alphabetSize == RU_ALPHABET_SIZE) {
                currentChar++;
            }
        }
        table[i / TABLE_COLUMNS][i % TABLE_COLUMNS] = currentChar;
        currentChar++;
    }
}

// Функция для шифрования текста
void encryptText(wchar_t text[], wchar_t encodedText[], wchar_t key[]) {
    int keyLength = wcslen(key);
    int textLength = wcslen(text);

    for (int i = 0; i < textLength; i++) {
        // Проверяем, является ли текущий символ буквой
        if (iswalpha(text[i])) {
            int index = i % keyLength;
            wchar_t shifted = text[i] + key[index] - L'А'; // Переводим символы в относительные позиции
            encodedText[i] = (shifted > L'Я') ? shifted - RU_ALPHABET_SIZE : shifted; // Обрабатываем переполнение
        } else {
            // Если текущий символ не буква, просто копируем его в зашифрованный текст
            encodedText[i] = text[i];
        }
    }

    encodedText[textLength] = L'\0';
}

// Функция для дешифрования текста
void decryptText(wchar_t encodedText[], wchar_t decryptedText[], wchar_t key[]) {
    int keyLength = wcslen(key);
    int textLength = wcslen(encodedText);

    for (int i = 0; i < textLength; i++) {
        // Проверяем, является ли текущий символ буквой
        if (iswalpha(encodedText[i])) {
            int index = i % keyLength;
            wchar_t shifted = encodedText[i] - (key[index] - L'А'); // Восстанавливаем исходное значение
            decryptedText[i] = (shifted < L'А') ? shifted + RU_ALPHABET_SIZE : shifted; // Обрабатываем переполнение
        } else {
            // Если текущий символ не буква, просто копируем его в дешифрованный текст
            decryptedText[i] = encodedText[i];
        }
    }

    decryptedText[textLength] = L'\0';
}


// Функция для сравнения исходного и дешифрованного текста
bool textsMatch(wchar_t original[], wchar_t decrypted[]) {
    return wcscmp(original, decrypted) == 0;
}
