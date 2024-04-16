#include <stdio.h>

#define N 7

int main() {
    int a = 1, b = 1, c, i, j;

    for (i = 0; i < N; i++) {
        c = a + b;
        for (j = 0; j <= i; j++) {
            printf("%d ", b);
            c = a + b;
            a = b;
            b = c;
        }
        printf("\n");
        a = 1;
        b = 1;
    }

    return 0;
}