#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Функция для шифрования и дешифрования текста
void encrypt_decrypt(char *text, char *key, int text_length, int key_length) {
    // Проходим по каждому символу текста
    for (int i = 0; i < text_length; ++i) {
        // Применяем операцию XOR к символу текста и символу ключа для шифрования и дешифрования
        text[i] = text[i] ^ key[i % key_length];
    }
}