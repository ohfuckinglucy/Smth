#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void finder(int a[], int i, int n, int* count) {
    if (i >= n) {
        return;
    }

    *count += (a[i] % 2 == 1 ? 1 : 0);
    finder(a, i + 2, n, count);
}

int main() {
    int* a;
    int i, n;
    int count = 0;

    srand(time(NULL));

    printf("Print size of massive: ");
    scanf("%d", &n);

    a = (int*)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        a[i] = rand() % 20;
    }

    finder(a, 0, n, &count);

    printf("Massive: ");
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\nCount = %d\n", count);
    free(a);

    return 0;
}