#include <stdio.h>
#include <stdlib.h>

void plusone(int *a){
    *a = *a + 1;
}

void muplitply(int *a){
    *a = *a * 2;
}

void swap(int *a, int *b){
    int term;
    term = *a;
    *a = *b;
    *b = term;
}

int main(){
    int i = 7, j = 7;

    printf("i = %d; j = %d\n", i, j);

    plusone(&i);
    muplitply(&j);

    printf("i = %d; j = %d\n", i, j);

    swap(&i, &j);

    printf("i = %d; j = %d\n", i, j);
}