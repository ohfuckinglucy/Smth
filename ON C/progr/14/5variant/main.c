#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Функция для переворота строки
void reverseString(char *start, char *end) {
    char temp;
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Функция для обработки строки, переворачивая каждое слово
void reverseWordsInLine(char *line) {
    char *word_start = NULL;
    char *temp = line;

    // Обработка строки, чтобы перевернуть каждое слово
    while (*temp) {
        // Находим начало слова
        if ((word_start == NULL) && (isalpha(*temp))) {
            word_start = temp;
        }
        // Находим конец слова и переворачиваем его
        if (word_start && (!isalpha(*temp) || *(temp + 1) == '\0')) {
            reverseString(word_start, temp - 1);
            word_start = NULL;
        }
        temp++;
    }
}

int main() {
    FILE *inputFile, *outputFile;
    char buffer[1024];

    // Открытие входного файла для чтения
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Ошибка открытия входного файла\n");
        return 1;
    }

    // Открытие выходного файла для записи
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Ошибка открытия выходного файла\n");
        fclose(inputFile);
        return 1;
    }

    // Чтение строки из входного файла и обработка
    while (fgets(buffer, sizeof(buffer), inputFile)) {
        reverseWordsInLine(buffer);
        fprintf(outputFile, "%s", buffer);
    }

    // Закрытие файлов
    fclose(inputFile);
    fclose(outputFile);

    printf("Обработка завершена. Результаты записаны в output.txt\n");
    return 0;
}
