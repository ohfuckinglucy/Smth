#include <stdio.h>
// 26 variant
// kolvo povtoreniy i index povtoreniy

int main() {
    int n = 5;
    int c[] = {1, 2, 3, 3, 4}; 

    int s = 0, b = 0, i, j, m;

    for (i = 0; i < n - 1; i++){
        for (j = i + 1, m = 0; j < n; j++)
            if (c[i] == c[j])
                m++;
        if (m > s)
            s = m, b = i;
    }

    printf("s = %d\n b = %d\n", s, b);
}