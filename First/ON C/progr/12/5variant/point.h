#include <stdio.h>

// Определение структуры Point
typedef struct {
    double x;
    double y;
    double z;
} Point;

double calculateDistance(Point A, Point B);

// статическая библиотека: 

// на стадии редактирования связей в состав исполняемого модуля включаются все функции, 
// для которых обнаружено обращение из текста исходной программы.

// gcc -c point.h -o point.o
// gcc -c functions.c -o functions.o
// ar rcs libpoint.a point.o functions.o

// gcc main.c -o static -L. -lpoint -lm

// ./static

// Динамическая библиотека:

// вызов модуля из динамической библиотеки происходит только на стадии выполнения программы.

// gcc -c main.c
// gcc -c -fPIC functions.c

// gcc -shared -o libpointd.so functions.o

// gcc -o dyn main.o -L. -lpointd -Wl,-rpath,. -lm

// ./dyn