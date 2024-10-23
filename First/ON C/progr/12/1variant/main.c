#include <stdio.h>
#include <stdlib.h>
#include "point.h"

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

int main() {
    T_t t1;
    T_t t2;
    T_t t3;
    printf("Введите координаты первой точки(x y через пробел): ");
    scanf("%d %d", &t1.x, &t1.y);
    printf("Введите координаты второй точки(x y через пробел): ");
    scanf("%d %d", &t2.x, &t2.y);
    printf("Введите координаты третьей точки(x y через пробел): ");
    scanf("%d %d", &t3.x, &t3.y);

    xy(t1, t2);
    st(t1, t2, t3);

    return 0;
}