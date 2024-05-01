#include <stdio.h>
// 1 variant
// polozjitelnost elementov

int main() {
    int n = 6;
    int A[] = {1, 2, 3, 4, 5, 0};

    int i;
    for (i = 0; i < n; i++) {
        if (A[i] < 0)
            break;
    }

    if (i == n)
        printf("1\n");
    else
        printf("0\n");
}