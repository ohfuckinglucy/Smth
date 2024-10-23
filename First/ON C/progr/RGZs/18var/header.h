#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

#define RU_ALPHABET_SIZE 33
#define EN_ALPHABET_SIZE 27
#define TABLE_ROWS 6
#define TABLE_COLUMNS 6
#define MAX_TEXT_SIZE 1000

void printTable(wchar_t table[][TABLE_COLUMNS], int rows, int columns);
void generateTable(wchar_t key[], wchar_t table[][TABLE_COLUMNS], int alphabetSize);
void removeDuplicates(wchar_t key[]);
void encryptText(wchar_t text[], wchar_t table[][TABLE_COLUMNS], wchar_t encodedText[], wchar_t key[], int rows, int columns);
void decryptText(wchar_t encodedText[], wchar_t table[][TABLE_COLUMNS], wchar_t key[], wchar_t decryptedText[], int rows, int columns);
bool textsMatch(wchar_t original[], wchar_t decrypted[]);
int detectLanguage(const wchar_t *text);
bool isInTable(wchar_t table[][TABLE_COLUMNS], wchar_t ch, int rows, int columns);

#endif // HEADER_H

/*
Инструкция для тебя:

1 - если в инпат пишешь русские слова, то выбирай русский метод таблицы? Если пишешь английский то англйиские
2 - это пиздец не надо сюда баготестов я ебал эту хуйнб делать внатуре ктож сука знал что внатуре до утра буду ебашить
3 - статическая библиотека вот команды
4 - есть один баг, который я не смог исправить. если ты вводишь слова с нечетным количеством буков(кот вместо коты например),
    то он выдает тебе не кот а котр или если ты на англ то catx, я делал это для того чтобы норм работала шифровка, а вот убрать эту
    хуйню не получилось. если препод скажет показывай. пиши слова с четным кол-вом букв.(ну лан я еще попробую пофиксить хз).
    так и не смог. . .

gcc -c main.c
gcc -c -fPIC func.c

gcc -shared -o libfunc.so func.o

gcc -o main main.o -L. -lfunc -Wl,-rpath,.

./main

./main input.txt output.txt key

ну или можешь просто ее скомпилировать как gcc main.c func.c -o main и запускать так же ./main input.txt output.txt key















*/