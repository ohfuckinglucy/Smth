#include "header.h"

// Функция для обмена двух символов
void wswap(wchar_t *a, wchar_t *b) {
    wchar_t temp = *a;
    *a = *b;
    *b = temp;
}

// Рекурсивная функция для генерации анаграмм
void generateAnagrams(wchar_t *word, int start, int end, FILE *output) {
    if (start == end) {
        wprintf(L"%ls\n", word);
        fwprintf(output, L"%ls\n", word);
    } else {
        for (int i = start; i <= end; i++) {
            wswap((word + start), (word + i));
            generateAnagrams(word, start + 1, end, output);
            wswap((word + start), (word + i)); // Обратный обмен
        }
    }
}
