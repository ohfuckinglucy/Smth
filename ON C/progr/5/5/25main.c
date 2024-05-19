// Программа находит индекс элемента массива c, 
// для которого количество элементов больше этого элемента равно количеству элементов меньше этого элемента. 

#include <stdio.h>

int findBalancedElement(int c[], int n) {
    int i, j, k1, k2;
    for (i = 0; i < n; i++) {
        k1 = k2 = 0; // Счетчики элементов меньше и больше текущего
        for (j = 0; j < n; j++) {
            if (c[i] != c[j]) {
                if (c[i] < c[j]) k1++;
                else k2++;
            }
        }
        if (k1 == k2) return i; // Возвращаем индекс, если количество элементов меньше равно количеству элементов больше
    }
    return -1; // Возвращаем -1, если такого элемента нет
}

int main() {
    int c[] = {5, 3, 8, 6, 2, 4, 7};
    int n = sizeof(c) / sizeof(c[0]);
    int index = findBalancedElement(c, n);

    if (index != -1) {
        printf("Balanced element found at index: %d\n", index);
    } else {
        printf("No balanced element found\n");
    }

    return 0;
}

// Для элемента 5: k1 = 3 (меньше: 3, 4, 2) и k2 = 3 (больше: 8, 6, 7) - элемент сбалансирован.