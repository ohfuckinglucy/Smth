#include <stdio.h>
#include <math.h>
#include "point.h"

void xy(T_t t1, T_t t2) {
    if (t1.x == t2.x && t1.y == t2.y) {
        printf("Точка параллельна как оси X, так и оси Y\n");
    } else if (t1.x == t2.x) {
        printf("Точка параллельна оси X\n");
    } else if (t1.y == t2.y) {
        printf("Точка параллельна оси Y\n");
    } else {
        printf("Точка не параллельна ни одной оси\n");
    }
}

void st(T_t t1, T_t t2, T_t t3) {
    float a = sqrt(pow(t2.x - t1.x, 2) + pow(t2.y - t1.y, 2));
    float b = sqrt(pow(t3.x - t2.x, 2) + pow(t3.y - t2.y, 2));
    float c = sqrt(pow(t1.x - t3.x, 2) + pow(t1.y - t3.y, 2));

    float s = (a + b + c) / 2;

    printf("%f\n", (sqrt(s * (s - a) * (s - b) * (s - c))));
}