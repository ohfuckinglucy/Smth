#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int factorial(int n) {
    int res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

int main() {
    float E = powf(10, -4);
    int m;
    float x = 0.7;
    float y,z;
    float chx = 1;

    while (m > 0) {
        y = powf(x, 2 * m);
        z = factorial(2 * m);
        chx += (y / z);
        if (coshf(chx) < E) {
            printf("%f\n", chx);
            break;
        }
        m++;
    }

    return 0;
}
