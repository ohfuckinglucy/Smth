#include <stdio.h>
#include <stdlib.h>

int main(){
    int *x;
    double *y;

    x = malloc(sizeof(int));
    y = malloc(sizeof(double));

    *x = 4;
    *y = 3.12345;

    printf("x: = %d\ny: = %f", *x, *y);

    free(x);
}