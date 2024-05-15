#include "header.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

void generateRandomArray(FILE *file, int size) {
    int i;
    srand(time(NULL));
    for (i = 0; i < size; i++) {
        int num = rand() % 100;
        fprintf(file, "%d ", num);
    }
}

double calculateAverage(int array[], int size) {
    int sum = 0;
    int i;
    for (i = 0; i < size; i++) {
        sum += array[i];
    }
    return (double)sum / size;
}

int findMinDeviation(int array[], int size) {
    double average = calculateAverage(array, size);
    int minDeviation = abs(array[0] - average);
    int i;
    for (i = 1; i < size; i++) {
        int deviation = abs(array[i] - average);
        if (deviation < minDeviation) {
            minDeviation = deviation;
        }
    }
    return minDeviation;
}

// int countNumbersInFile(FILE *file) {
//     int count = 0;
//     int number;
//     while (fscanf(file, "%d", &number) == 1) {
//         count++;
//     }
//     rewind(file);
//     return count;
// }