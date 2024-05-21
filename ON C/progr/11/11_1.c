#include <stdio.h>
#include <math.h>



double factorial(int n) {
    if (n == 0 || n == 1) {
        return 1.0;
    } else {
        return n * factorial(n - 1);
    }
}

double COSH(double x, int n) {
    double E = pow(10, -4);
    double term = 1;
    term += pow(x, 2 * n) / factorial(2 * n);
    if (term >= E) {
        return term + COSH(x, n + 1);
    }
    return term;
}

int main() {
    double x = 0.7;
    double coshX = COSH(x, 0);
    int n = 1;

    printf("cosh(%f) = %f\n", x, coshX);

    return 0;
}