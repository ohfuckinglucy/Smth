#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include "header.h"

void get_coordinates(wchar_t c, wchar_t *row, wchar_t *col) {
    if (c == L' ') {
        *row = *col = L' ';
        return;
    }

    wchar_t table[6][6] = {
        {L'А', L'Б', L'В', L'Г', L'Д', L'Е'},
        {L'Ж', L'З', L'И', L'К', L'Л', L'М'},
        {L'Н', L'О', L'П', L'Р', L'С', L'Т'},
        {L'У', L'Ф', L'Х', L'Ц', L'Ч', L'Ш'},
        {L'Щ', L'Ъ', L'Ы', L'Ь', L'Э', L'Ю'},
        {L'Я', L'.', L',', L'-', L':'}
    };

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (table[i][j] == c) {
                *row = L'А' + i;
                *col = L'А' + j;
                return;
            }
        }
    }
    *row = *col = L'\0';
}

void encrypt(const wchar_t *plaintext, wchar_t *ciphertext) {
    while (*plaintext) {
        wchar_t row, col;
        get_coordinates(*plaintext++, &row, &col);
        *ciphertext++ = row;
        *ciphertext++ = col;
    }
    *ciphertext = L'\0';
}

void decrypt(const wchar_t *ciphertext, wchar_t *plaintext) {
    wchar_t table[6][6] = {
        {L'А', L'Б', L'В', L'Г', L'Д', L'Е'},
        {L'Ж', L'З', L'И', L'К', L'Л', L'М'},
        {L'Н', L'О', L'П', L'Р', L'С', L'Т'},
        {L'У', L'Ф', L'Х', L'Ц', L'Ч', L'Ш'},
        {L'Щ', L'Ъ', L'Ы', L'Ь', L'Э', L'Ю'},
        {L'Я', L'.', L',', L'-', L':'}
    };

    while (*ciphertext) {
        wchar_t row = *ciphertext++;
        wchar_t col = *ciphertext++;
        if (row == L' ' && col == L' ') {
            *plaintext++ = L' ';
            continue;
        }
        if (row < L'А' || row > L'Я' || col < L'А' || col > L'Я') {
            // Если символы выходят за пределы таблицы, записываем пустой символ
            *plaintext++ = L' ';
            continue;
        }
        *plaintext++ = table[row - L'А'][col - L'А'];
    }
    *plaintext = L'\0';
}

void cleanText(wchar_t *text) {
    size_t len = wcslen(text);
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (text[i] != L'\n' && text[i] != L'\r') {
            text[j++] = text[i];
        }
    }
    text[j] = L'\0'; // Добавляем символ конца строки
}
