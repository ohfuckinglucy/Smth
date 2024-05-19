#include <stdio.h>
#include "point.h"

int main() {
    Point A, B;

    // Ввод координат первой точки
    printf("Введите координаты точки A (x y z): ");
    scanf("%lf %lf %lf", &A.x, &A.y, &A.z);

    // Ввод координат второй точки
    printf("Введите координаты точки B (x y z): ");
    scanf("%lf %lf %lf", &B.x, &B.y, &B.z);

    // Вычисление расстояния между точками
    double distance = calculateDistance(A, B);

    // Вывод результата
    printf("Расстояние между точками A и B: %.2lf\n", distance);

    return 0;
}
