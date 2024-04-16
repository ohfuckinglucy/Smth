#ifndef SORTING_H
#define SORTING_H

void printArray(int arr[], int n);
void swap(int* a, int* b, int* swaps);
void fillArray(int arr[], int n, int fillType);
void shellSort(int arr[], int n, int* comparisons, int* swaps);
void insertionSort(int arr[], int n, int* comparisons, int* swaps);
void bubbleSort(int arr[], int n, int* comparisons, int* swaps);
void countingSort(int arr[], int n, int* comparisons, int* swaps);

#endif