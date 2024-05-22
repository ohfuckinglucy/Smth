#include "header.h"
#include <stdlib.h>
#include <string.h>

// Функция для шифрования
char* encrypt(const char* text, int rows, int cols) {
    int length = strlen(text);
    char* table = (char*)calloc(rows * cols, sizeof(char));
    char* cipher = (char*)calloc(rows * cols + 1, sizeof(char));

    for (int i = 0; i < rows * cols; i++) {
        table[i] = (i < length) ? text[i] : '_'; // Заполняем пустые ячейки символом '_'
    }
    
    for (int j = 0, k = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++, k++) {
            cipher[k] = table[i * cols + j];
        }
    }
    
    free(table);
    return cipher;
}

// Функция для дешифрования
char* decrypt(const char* cipher, int rows, int cols) {
    int length = strlen(cipher);
    char* table = (char*)calloc(rows * cols, sizeof(char));
    char* text = (char*)calloc(rows * cols + 1, sizeof(char));

    for (int j = 0, k = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++, k++) {
            table[i * cols + j] = cipher[k];
        }
    }
    
    for (int i = 0, k = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++, k++) {
            text[k] = table[i * cols + j];
        }
    }
    
    // Удаление добавленных символов '_'
    for (int i = length - 1; i >= 0; i--) {
        if (text[i] == '_') {
            text[i] = '\0';
        } else {
            break;
        }
    }
    
    free(table);
    return text;
}

// Функция для освобождения памяти
void free_memory(char* ptr) {
    free(ptr);
}
