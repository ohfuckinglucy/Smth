#include <stdio.h>
#include <math.h>

// Функция для вычисления факториала
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

// Рекурсивная функция для вычисления shx
double shx(double x, int n, double term, double E) {
    if (fabs(term) < E) {
        return term;
    } else {
        double next_term = term * x * x / ((2 * n + 2) * (2 * n + 3));
        return term + shx(x, n + 1, next_term, E);
    }
}

int main() {
    double x = 1.7;
    double E = 1e-3;
    double initial_term = x; // первый член ряда x

    double result = shx(x, 0, initial_term, E);
    printf("shx(%f) = %f\n", x, result);

    return 0;
}
