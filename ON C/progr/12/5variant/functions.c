#include <stdio.h>
#include <math.h>
#include "point.h"

// Функция для вычисления расстояния между двумя точками
double calculateDistance(Point A, Point B) {
    return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2));
}