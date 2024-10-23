#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

#define ALPHABET_SIZE 33 // 33 буквы в русском алфавите, включая пробел и дополнительные символы
#define TABLE_ROWS 6
#define TABLE_COLUMNS 6 // Расширенная таблица для русского алфавита
#define MAX_TEXT_SIZE 1000

void printTable(wchar_t table[][TABLE_COLUMNS]) {
    for (int i = 0; i < TABLE_ROWS; i++) {
        for (int j = 0; j < TABLE_COLUMNS; j++) {
            wprintf(L"%lc ", table[i][j]);
        }
        wprintf(L"\n");
    }
}

void generateTable(wchar_t key[], wchar_t table[][TABLE_COLUMNS]) {
    int keyLength = wcslen(key);
    int i, j;

    // Заполнение таблицы ключевым словом
    for (i = 0; i < keyLength; i++) {
        table[i / TABLE_COLUMNS][i % TABLE_COLUMNS] = key[i];
    }

    // Дополнение оставшейся части таблицы символами алфавита, исключая символы из ключа
    wchar_t currentChar = L'А'; // Первая буква русского алфавита
    for (; i < TABLE_ROWS * TABLE_COLUMNS; i++) {
        // Проверка, чтобы избежать дублирования букв из ключа
        if (!wcschr(key, currentChar)) {
            table[i / TABLE_COLUMNS][i % TABLE_COLUMNS] = currentChar;
            currentChar++;
            if (currentChar == L'Ё') // Пропускаем Ё, так как она идет после Е
                currentChar++;
        } else {
            currentChar++;
            i--; // Пропускаем заполненные буквой из ключа столбцы
        }
    }
}

void removeDuplicates(wchar_t key[]) {
    int len = wcslen(key);
    int currentIndex = 0;

    for (int i = 0; i < len; i++) {
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
    key[currentIndex] = L'\0';
}

void encryptText(wchar_t text[], wchar_t table[][TABLE_COLUMNS], wchar_t encodedText[], wchar_t key[]) {
    int i_first, j_first, i_second, j_second;
    wchar_t s1[2], s2[2];
    int len = wcslen(text);
    int encodedTextIndex = 0;

    // Проверяем, является ли длина текста нечётной
    int isOddLength = len % 2 != 0;

    // Добавляем символ "Р", если длина текста нечётная
    if (isOddLength) {
        text[len++] = L'Р';
        text[len] = L'\0';
    }

    for (int i = 0; i < len; i += 2) {
        // Находим координаты первого символа пары
        for (int r = 0; r < TABLE_ROWS; r++) {
            for (int c = 0; c < TABLE_COLUMNS; c++) {
                if (text[i] == table[r][c]) {
                    i_first = r;
                    j_first = c;
                    break;
                }
            }
        }

        // Находим координаты второго символа пары
        for (int r = 0; r < TABLE_ROWS; r++) {
            for (int c = 0; c < TABLE_COLUMNS; c++) {
                if (text[i + 1] == table[r][c]) {
                    i_second = r;
                    j_second = c;
                    break;
                }
            }
        }

        // Шифруем символы
        if (i_first == i_second) {
            s1[0] = table[i_first][(j_first + 1) % TABLE_COLUMNS];
            s1[1] = L'\0';
            s2[0] = table[i_second][(j_second + 1) % TABLE_COLUMNS];
            s2[1] = L'\0';
        } else if (j_first == j_second) {
            s1[0] = table[(i_first + 1) % TABLE_ROWS][j_first];
            s1[1] = L'\0';
            s2[0] = table[(i_second + 1) % TABLE_ROWS][j_second];
            s2[1] = L'\0';
        } else {
            s1[0] = table[i_first][j_second];
            s1[1] = L'\0';
            s2[0] = table[i_second][j_first];
            s2[1] = L'\0';
        }

        // Записываем зашифрованные символы в строку
        encodedText[encodedTextIndex++] = s1[0];
        encodedText[encodedTextIndex++] = s2[0];
    }

    encodedText[encodedTextIndex] = L'\0';
}

void decryptText(wchar_t encodedText[], wchar_t table[][TABLE_COLUMNS], wchar_t key[]) {
    int i_first, j_first, i_second, j_second;
    wchar_t s1[2], s2[2];
    int len = wcslen(encodedText);

    for (int i = 0; i < len; i += 2) {
        // Находим координаты первого символа пары
        for (int r = 0; r < TABLE_ROWS; r++) {
            for (int c = 0; c < TABLE_COLUMNS; c++) {
                if (encodedText[i] == table[r][c]) {
                    i_first = r;
                    j_first = c;
                    break;
                }
            }
        }

        // Находим координаты второго символа пары
        for (int r = 0; r < TABLE_ROWS; r++) {
            for (int c = 0; c < TABLE_COLUMNS; c++) {
                if (encodedText[i + 1] == table[r][c]) {
                    i_second = r;
                    j_second = c;
                    break;
                }
            }
        }

        // Дешифруем символы
            if (i_first == i_second) {
            s1[0] = table[i_first][(j_first - 1 + TABLE_COLUMNS) % TABLE_COLUMNS];
            s1[1] = L'\0';
            s2[0] = table[i_second][(j_second - 1 + TABLE_COLUMNS) % TABLE_COLUMNS];
            s2[1] = L'\0';
        }  else if (j_first == j_second) {
            s1[0] = table[(i_first - 1 + TABLE_ROWS) % TABLE_ROWS][j_first];
            s1[1] = L'\0';
            s2[0] = table[(i_second - 1 + TABLE_ROWS) % TABLE_ROWS][j_second];
            s2[1] = L'\0';
        } else {
            s1[0] = table[i_first][j_second];
            s1[1] = L'\0';
            s2[0] = table[i_second][j_first];
            s2[1] = L'\0';
        }

        // Выводим дешифрованные символы
        wprintf(L"%ls%ls", s1, s2);
    }
    wprintf(L"\n");
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    // Проверка на наличие аргументов командной строки
    if (argc != 4) {
        wprintf(L"Использование: %s <файл_ввода> <файл_вывода_шифра> <ключевое_слово>\n", argv[0]);
        return 1;
    }

    wchar_t *key = (wchar_t *)malloc(MAX_TEXT_SIZE * sizeof(wchar_t));
    wchar_t *plainText = (wchar_t *)malloc(MAX_TEXT_SIZE * sizeof(wchar_t));
    wchar_t *encodedText = (wchar_t *)malloc(MAX_TEXT_SIZE * sizeof(wchar_t));
    
    wchar_t table[TABLE_ROWS][TABLE_COLUMNS];

    // Запрос ключевого слова из аргументов командной строки
    mbstowcs(key, argv[3], MAX_TEXT_SIZE);

    removeDuplicates(key);

    // Генерация таблицы шифрования
    generateTable(key, table);

    // Открытие файла для чтения
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        wprintf(L"Ошибка открытия файла %s\n", argv[1]);
        return 1;
    }

    // Чтение текста из файла
    fgetws(plainText, MAX_TEXT_SIZE, inputFile);
    fclose(inputFile);

    // Удаление символа новой строки, если есть
    if (wcschr(plainText, L'\n') != NULL) {
        plainText[wcslen(plainText) - 1] = L'\0';
    }

    // Зашифровка текста
    encryptText(plainText, table, encodedText, key);

    // Открытие файла для записи зашифрованного текста
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        wprintf(L"Ошибка открытия файла %s\n", argv[2]);
        return 1;
    }

    // Запись зашифрованного текста в файл
    fputws(encodedText, outputFile);
    fclose(outputFile);

    // Вывод зашифрованного текста
    wprintf(L"Зашифрованный текст записан в файл: %s\n", argv[2]);

    // Вывод таблицы шифрования
    wprintf(L"Таблица шифрования:\n");
    printTable(table);

    // Вывод ключевого слова
    wprintf(L"Ключевое слово: %ls\n", key);

    // Вывод зашифрованного текста
    wprintf(L"Зашифрованный текст: %ls\n", encodedText);

    // Вывод дешифрованного текста
    wprintf(L"Дешифрованный текст: ");
    decryptText(encodedText, table, key);

    // Освобождение выделенной памяти
    free(key);
    free(plainText);
    free(encodedText);

    return 0;
}