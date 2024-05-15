#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для шифрования строки
char* encrypt(char* plaintext, char* keyword) {
    int keyword_length = strlen(keyword);
    int plaintext_length = strlen(plaintext);

    // Создаем таблицу для шифрования
    char table[keyword_length][plaintext_length / keyword_length + 1];

    // Заполняем таблицу по столбцам
    int index = 0;
    for (int i = 0; i < keyword_length; i++) {
        for (int j = 0; j < plaintext_length / keyword_length + 1; j++) {
            if (index < plaintext_length)
                table[i][j] = plaintext[index++];
            else
                table[i][j] = ' ';
        }
    }

    // Переставляем столбцы согласно отсортированному ключевому слову
    for (int i = 0; i < keyword_length; i++) {
        for (int j = i + 1; j < keyword_length; j++) {
            if (keyword[i] > keyword[j]) {
                char temp;
                // Переставляем столбцы в таблице
                for (int k = 0; k < plaintext_length / keyword_length + 1; k++) {
                    temp = table[i][k];
                    table[i][k] = table[j][k];
                    table[j][k] = temp;
                }
            }
        }
    }

    // Формируем зашифрованную строку
    char* ciphertext = (char*)malloc(plaintext_length + 1);
    index = 0;
    for (int i = 0; i < plaintext_length / keyword_length + 1; i++) {
        for (int j = 0; j < keyword_length; j++) {
            if (index < plaintext_length)
                ciphertext[index++] = table[j][i];
        }
    }
    ciphertext[plaintext_length] = '\0';

    return ciphertext;
}

// Функция для дешифрования строки
char* decrypt(char* ciphertext, char* keyword) {
    int keyword_length = strlen(keyword);
    int ciphertext_length = strlen(ciphertext);
    int column_length = ciphertext_length / keyword_length;

    // Создаем таблицу для дешифрования
    char table[keyword_length][column_length];

    // Заполняем таблицу по строкам
    int index = 0;
    for (int i = 0; i < column_length; i++) {
        for (int j = 0; j < keyword_length; j++) {
            table[j][i] = ciphertext[index++];
        }
    }

    // Переставляем столбцы обратно согласно ключевому слову
    for (int i = 0; i < keyword_length; i++) {
        for (int j = i + 1; j < keyword_length; j++) {
            if (keyword[i] > keyword[j]) {
                char temp;
                // Переставляем столбцы в таблице
                for (int k = 0; k < column_length; k++) {
                    temp = table[i][k];
                    table[i][k] = table[j][k];
                    table[j][k] = temp;
                }
            }
        }
    }

    // Формируем расшифрованную строку
    char* plaintext = (char*)malloc(ciphertext_length + 1);
    index = 0;
    for (int i = 0; i < keyword_length; i++) {
        for (int j = 0; j < column_length; j++) {
            plaintext[index++] = table[i][j];
        }
    }
    plaintext[ciphertext_length] = '\0';

    return plaintext;
}

int main() {
    char keyword[] = "мяу";
    char plaintext[] = "приветик";

    // Шифрование
    char* ciphertext = encrypt(plaintext, keyword);
    printf("Зашифрованное сообщение: %s\n", ciphertext);

    // Дешифрование
    char* decrypted_text = decrypt(ciphertext, keyword);
    printf("Расшифрованное сообщение: %s\n", decrypted_text);

    free(ciphertext);
    free(decrypted_text);

    return 0;
}
