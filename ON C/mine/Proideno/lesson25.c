#include <stdio.h>
#include <stdlib.h>

void freemas(int **p){
    free(p);
    *p = NULL;
}

int main(){
    int *mas = NULL;
    int n;
    printf("Print n\n");
    scanf("%d", &n);
    mas = malloc(sizeof(int) * n);

    mas[0] = 1;

    for (int i = 1; i < n; i ++){
        mas[i] = mas[i-1] * 2;
    }
    for (int i = 0; i < n; i ++){
        printf("mas %d: = %d\n", i, mas[i]);
    }

    free(mas);
    mas = NULL;

    n = n + 4;

    mas = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i ++){
        mas[i] = 0;
    }
    for (int i = 0; i < n; i ++){
        printf("mas %d: = %d\n", i, mas[i]);
    }

    freemas(&mas);

    if (mas == NULL){
        printf("Okay!\n");
    }

}