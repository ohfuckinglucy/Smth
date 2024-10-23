#ifndef HEADER_H
#define HEADER_H

char* encrypt(const char* text, int rows, int cols);
char* decrypt(const char* text, int rows, int cols);
void free_memory(char* pointer);

#endif


// запись в динамическую библиотеку

// gcc -c main.c
// gcc -c -fPIC functions.c

// gcc -shared -o libcipher.so functions.o

// gcc -o main main.o -L. -lcipher -Wl,-rpath,.

// ./main