#include "header.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    // Проверяем количество аргументов командной строки
    if (argc != 4) {
        wprintf(L"Использование: %s <файл_ввода> <файл_вывода_шифра> <ключевое_слово>\n", argv[0]);
        return 1;
    }

    int languageChoice;
    wprintf(L"Choose the language:\n1. Russian (русский)\n2. English\n");
    wscanf(L"%d", &languageChoice);

    // Проверка выбора языка
    if (languageChoice != 1 && languageChoice != 2) {
        wprintf(L"Invalid choice.\n");
        return 1;
    }

    // Выделяем память для всех необходимых строк
    wchar_t *key = (wchar_t *)malloc(MAX_TEXT_SIZE * sizeof(wchar_t));
    wchar_t *plainText = (wchar_t *)malloc(MAX_TEXT_SIZE * sizeof(wchar_t));
    wchar_t *encodedText = (wchar_t *)malloc(MAX_TEXT_SIZE * sizeof(wchar_t));
    wchar_t *decryptedText = (wchar_t *)malloc(MAX_TEXT_SIZE * sizeof(wchar_t));

    if (!key || !plainText || !encodedText || !decryptedText) {
        wprintf(L"Ошибка выделения памяти.\n");
        free(key);
        free(plainText);
        free(encodedText);
        free(decryptedText);
        return 1;
    }
    
    wchar_t table[TABLE_ROWS][TABLE_COLUMNS];

    // Преобразуем ключевое слово из multibyte в wide character
    mbstowcs(key, argv[3], MAX_TEXT_SIZE);

    // Удаляем дубликаты из ключа
    removeDuplicates(key);

    // Проверяем наличие символов в ключевом слове
    if (wcslen(key) == 0) {
        wprintf(L"Ошибка: ключевое слово не содержит символов.\n");
        free(key);
        free(plainText);
        free(encodedText);
        free(decryptedText);
        return 1;
    }

//     for (int i = 0; key[i] != L'\0'; i++) {
//     if (!isInTable(table, key[i], TABLE_ROWS, TABLE_COLUMNS)) {
//         wprintf(L"Ошибка: Один из символов не присутствует в таблице шифрования.\n", key[i]);
//         free(key);
//         free(plainText);
//         free(encodedText);
//         free(decryptedText);
//         return 1;
//     }
// }

    // Генерируем таблицу шифрования на основе ключа и выбранного языка
    generateTable(key, table, (languageChoice == 1) ? RU_ALPHABET_SIZE : EN_ALPHABET_SIZE);

    // Проверяем, содержатся ли все символы из ключевого слова в таблице
    int keyLength = wcslen(key);
    for (int i = 0; i < keyLength; i++) {
        if (!isInTable(table, key[i], TABLE_ROWS, TABLE_COLUMNS)) {
            wprintf(L"Предупреждение: символ \"%lc\" отсутствует в таблице шифрования.\n", key[i]);
            break;
        }
    }

    // Открываем файл для чтения исходного текста
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        wprintf(L"Ошибка открытия файла %s\n", argv[1]);
        free(key);
        free(plainText);
        free(encodedText);
        free(decryptedText);
        return 1;
    }

    // Читаем содержимое файла в plainText
    fgetws(plainText, MAX_TEXT_SIZE, inputFile);
    fclose(inputFile);

    // Удаляем символ новой строки, если он есть
    if (wcschr(plainText, L'\n') != NULL) {
        plainText[wcslen(plainText) - 1] = L'\0';
    }

    // Определяем язык текста
    int detectedLanguage = detectLanguage(plainText);
    if (detectedLanguage == -1) {
        wprintf(L"Ошибка: текст содержит смешанные символы русского и английского языков.\n");
        free(key);
        free(plainText);
        free(encodedText);
        free(decryptedText);
        return 1;
    }

    // Проверяем, соответствует ли выбранный язык языку текста
    if ((detectedLanguage == 1 && languageChoice != 1) || (detectedLanguage == 2 && languageChoice != 2)) {
        wprintf(L"Ошибка: выбранный язык не соответствует языку текста в файле.\n");
        free(key);
        free(plainText);
        free(encodedText);
        free(decryptedText);
        return 1;
    }

    // Шифруем текст
    encryptText(plainText, table, encodedText, key, TABLE_ROWS, TABLE_COLUMNS);

    // Открываем файл для записи зашифрованного текста
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        wprintf(L"Ошибка открытия файла %s\n", argv[2]);
        free(key);
        free(plainText);
        free(encodedText);
        free(decryptedText);
        return 1;
    }

    // Записываем зашифрованный текст в файл
    fputws(encodedText, outputFile);
    fclose(outputFile);

    wprintf(L"Зашифрованный текст записан в файл: %s\n", argv[2]);
    wprintf(L"Таблица шифрования:\n");
    printTable(table, TABLE_ROWS, TABLE_COLUMNS);
    wprintf(L"Ключевое слово: %ls\n", key);
    wprintf(L"Зашифрованный текст: %ls\n", encodedText);

    // Дешифруем текст
    decryptText(encodedText, table, key, decryptedText, TABLE_ROWS, TABLE_COLUMNS);

    // Проверяем, совпадает ли дешифрованный текст с исходным
    if (textsMatch(plainText, decryptedText)) {
        wprintf(L"Дешифрованный текст совпадает с исходным текстом\n");
    } else {
        wprintf(L"Ошибка: дешифрованный текст не совпадает с исходным текстом.\n");
    }

    // Освобождаем вывыделенную память
    free(key);
    free(plainText);
    free(encodedText);
    free(decryptedText);

    return 0;
}