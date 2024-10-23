#include <stdio.h>
// 36 variant
// вроде должно делить проверить себя на не имение нуля и на то что не делится на свои цифры но чтото тут не то
int main() {
    int j, a, s, v, n, k;
    int A[30];

    v = 30;

    for (j = 0, a = 10; a < v; a++) {
        for (s = 0, n = a; n != 0; n = n / 10) {
            k = n % 10;
            if (k != 0 && a % k != 0) {
                s = 1;
                break;
            }
        }
        if (s == 0)
            A[j++] = a;
    }

    for (int i = 0; i < j; i++) {
        printf("%d ", A[i]);
    }
}