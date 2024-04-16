#include <stdio.h>

void printHexadecimal(unsigned int num) {
    printf("0x");
    for (int i = sizeof(num) * 2 - 1; i >= 0; i--) {
        unsigned int tetrad = (num >> (i * 4)) & 0xF;
        if (tetrad < 10)
            printf("%u", tetrad);
        else
            printf("%c", 'A' + (tetrad - 10));
    }
    printf("\n");
}

int main() {
    unsigned int A;
    printf("Введите число: ");
    scanf("%d", &A);
    printf("ваше число в 16-ой системе счисления: ");
    printHexadecimal(A);
    return 0;
}
