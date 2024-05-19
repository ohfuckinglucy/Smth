#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_LINES 1000

int main() {
    FILE *inputFile, *outputFile;
    char *lines[MAX_LINES];
    char buffer[MAX_LINE_LENGTH];
    int lineCount = 0;

    // Открываем файл для чтения
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        perror("Ошибка при открытии файла для чтения");
        return 1;
    }

    // Читаем строки из файла и сохраняем их в массив
    while (fgets(buffer, MAX_LINE_LENGTH, inputFile)) {
        lines[lineCount] = malloc(strlen(buffer) + 1);
        if (lines[lineCount] == NULL) {
            printf("Ошибка выделения памяти\n");
            return 1;
        }
        strcpy(lines[lineCount], buffer);
        lineCount++;
    }

    // Закрываем входной файл
    fclose(inputFile);

    // Открываем файл для записи
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Ошибка при открытии файла для записи\n");
        return 1;
    }

    // Записываем строки в обратном порядке
    for (int i = lineCount - 1; i >= 0; i--) {
        fputs(lines[i], outputFile);
        free(lines[i]); // Освобождаем память после записи строки
    }

    // Закрываем выходной файл
    fclose(outputFile);

    return 0;
}
