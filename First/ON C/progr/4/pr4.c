#include <stdio.h>

int main() {
    unsigned int a;
    int k;

        
    unsigned int bits_count = sizeof(unsigned int) * 8;
    k %= bits_count;
    
    printf("Исходное число: %d\n", a);
    
    for (int i = 0; i < k; ++i) {
        unsigned int left_bit = (a >> (bits_count - 1)) & 1;
        a = ((a << 1) & (~0u)) | left_bit;
    }
    
    printf("Число после циклического сдвига на %d позиций влево: %d\n", k, a);
    
    return 0;
}
