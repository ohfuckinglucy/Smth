#ifndef PLAYHEADER_H
#define PLAYHEADER_H

#include <wchar.h>
#include <stdbool.h>

#define TABLE_ROWS 6
#define TABLE_COLUMNS 6
#define MAX_TEXT_SIZE 100

#define RU_ALPHABET_SIZE 33 // Например, размер кириллического алфавита

// Функция для печати таблицы шифрования
void printTable(wchar_t table[][TABLE_COLUMNS], int rows, int columns);

// Функция для удаления дубликатов из ключа
void removeDuplicates(wchar_t key[]);

// Функция для генерации таблицы шифрования на основе ключа
void generateTable(wchar_t key[], wchar_t table[][TABLE_COLUMNS], int alphabetSize);

// Функция для шифрования текста
void encryptText(wchar_t text[], wchar_t encodedText[], wchar_t key[]);

// Функция для дешифрования текста
void decryptText(wchar_t encodedText[], wchar_t decryptedText[], wchar_t key[]);

// Функция для сравнения исходного и дешифрованного текста
bool textsMatch(wchar_t original[], wchar_t decrypted[]);

#endif

/*

gcc -c PlayKey.c
gcc -c -fPIC playfunc.c

gcc -shared -o libfunc.so playfunc.o

gcc -o play PlayKey.o -L. -lfunc -Wl,-rpath,.

./play

./play input.txt output.txt key


gcc -c DePlayKey.c
gcc -c -fPIC playfunc.c

gcc -shared -o libfunc.so playfunc.o

gcc -o deplay DePlayKey.o -L. -lfunc -Wl,-rpath,.

./deplay

./deplay input.txt output.txt key (first input)




*/