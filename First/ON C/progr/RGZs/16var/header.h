#ifndef HEADER_H
#define HEADER_H

#include <wchar.h>

void get_coordinates(wchar_t c, wchar_t *row, wchar_t *col);
void encrypt(const wchar_t *plaintext, wchar_t *ciphertext);
void decrypt(const wchar_t *ciphertext, wchar_t *plaintext);
void cleanText(wchar_t *text);

#endif
/*
    gcc -c Poliby.c
    gcc -c -fPIC functions.c

    gcc -shared -o libpointd.so functions.o

    gcc -o pol Poliby.o -L. -lpointd -Wl,-rpath,.

    ./pol


    gcc -c DePoliby.c
    gcc -c -fPIC functions.c

    gcc -shared -o libpointd.so functions.o

    gcc -o depol DePoliby.o -L. -lpointd -Wl,-rpath,.

    ./depol
*/