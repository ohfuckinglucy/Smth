#include "header.h"

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
    wchar_t currentChar = (alphabetSize == RU_ALPHABET_SIZE) ? L'А' : L'A';
    for (; i < TABLE_ROWS * TABLE_COLUMNS; i++) {
        while (wcschr(key, currentChar) != NULL || currentChar == L' ') { // Пропускаем символы из ключа и пробелы
            currentChar++;
            if (currentChar == L'Ё' && alphabetSize == RU_ALPHABET_SIZE) {
                currentChar++;
            } else if (currentChar == L'[' && alphabetSize == EN_ALPHABET_SIZE) {
                currentChar = L'a';
            }
        }
        table[i / TABLE_COLUMNS][i % TABLE_COLUMNS] = currentChar;
        currentChar++;
    }
}


// Функция для шифрования текста
void encryptText(wchar_t text[], wchar_t table[][TABLE_COLUMNS], wchar_t encodedText[], wchar_t key[], int rows, int columns) {
    int i_first, j_first, i_second, j_second;
    wchar_t s1, s2;
    int len = wcslen(text);
    int encodedTextIndex = 0;

    for (int i = 0; i < len; i += 2) {
        // Поиск первой буквы в таблице
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                if (text[i] == table[r][c]) {
                    i_first = r;
                    j_first = c;
                    break;
                }
            }
        }

        // Поиск второй буквы в таблице
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                if (text[i + 1] == table[r][c]) {
                    i_second = r;
                    j_second = c;
                    break;
                }
            }
        }

        // Применение правил шифрования
        if (i_first == i_second) {
            s1 = table[i_first][(j_first + 1) % columns];
            s2 = table[i_second][(j_second + 1) % columns];
        } else if (j_first == j_second) {
            s1 = table[(i_first + 1) % rows][j_first];
            s2 = table[(i_second + 1) % rows][j_second];
        } else {
            s1 = table[i_first][j_second];
            s2 = table[i_second][j_first];
        }

        encodedText[encodedTextIndex++] = s1;
        encodedText[encodedTextIndex++] = s2;
    }

    encodedText[encodedTextIndex] = L'\0';
}

// Функция для дешифрования текста
void decryptText(wchar_t encodedText[], wchar_t table[][TABLE_COLUMNS], wchar_t key[], wchar_t decryptedText[], int rows, int columns) {
    int i_first, j_first, i_second, j_second;
    wchar_t s1, s2;
    int len = wcslen(encodedText);
    int decryptedTextIndex = 0;

    for (int i = 0; i < len; i += 2) {
        // Поиск первой буквы в таблице
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                if (encodedText[i] == table[r][c]) {
                    i_first = r;
                    j_first = c;
                    break;
                }
            }
        }

        // Поиск второй буквы в таблице
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                if (encodedText[i + 1] == table[r][c]) {
                    i_second = r;
                    j_second = c;
                    break;
                }
            }
        }

        // Применение правил дешифрования
        if (i_first == i_second) {
            s1 = table[i_first][(j_first - 1 + columns) % columns];
            s2 = table[i_second][(j_second - 1 + columns) % columns];
        } else if (j_first == j_second) {
            s1 = table[(i_first - 1 + rows) % rows][j_first];
            s2 = table[(i_second - 1 + rows) % rows][j_second];
        } else {
            s1 = table[i_first][j_second];
            s2 = table[i_second][j_first];
        }

        // Проверка на символы, которые не должны быть в выходном тексте
        if (s1 != L'Р') {
            decryptedText[decryptedTextIndex++] = s1;
        }
        if (s2 != L'Р') {
            decryptedText[decryptedTextIndex++] = s2;
        }
    }

    decryptedText[decryptedTextIndex] = L'\0';
}

// Функция для сравнения исходного и дешифрованного текста
bool textsMatch(wchar_t original[], wchar_t decrypted[]) {
    return wcscmp(original, decrypted) == 0;
}

// Функция для определения языка текста
int detectLanguage(const wchar_t *text) {
    int hasRussian = 0;
    int hasEnglish = 0;

    while (*text) {
        if ((*text >= L'А' && *text <= L'я') || *text == L'Ё' || *text == L'ё') {
            hasRussian = 1;
        }
        if ((*text >= L'A' && *text <= L'Z') || (*text >= L'a' && *text <= L'z')) {
            hasEnglish = 1;
        }
        text++;
    }

    if (hasRussian && hasEnglish) {
        return -1; // Смешанный текст
    } else if (hasRussian) {
        return 1; // Русский текст
    } else if (hasEnglish) {
        return 2; // Английский текст
    }

    return 0; // Неопределенный
}
// Функция для проверки наличия символа в таблице
bool isInTable(wchar_t table[][TABLE_COLUMNS], wchar_t ch, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (table[i][j] == ch) {
                return true;
            }
        }
    }
    return false;
}