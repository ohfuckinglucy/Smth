#ifndef HEADER_H
#define HEADER_H

void sortingcol(char *key, int key_len, int rows, char **arr, int *original_index);
void decrypt(char *key, int key_len, int rows, char **arr, int *original_index);

#endif

// Динамическая библиотека:

// gcc -c main.c
// gcc -c -fPIC functions.c

// gcc -shared -o libfunc.so functions.o

// gcc -o main main.o -L. -lfunc -Wl,-rpath,.

// ./main

// ./main key.txt input.txt output.txt

// первым подается ключ потом входной файл и потом выходной.