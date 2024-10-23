#ifndef SORTING_H
#define SORTING_H

// Объявления функций сортировок
void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void bubbleSort(int arr[], int n);

#endif /* SORTING_H */

// запись в динамическую библиотеку

// gcc -c main.c
// gcc -c -fPIC bubble_sort.c quick_sort.c

// gcc -shared -o libsort.so bubble_sort.c quick_sort.c

// gcc -o main main.o -L. -lsort -Wl,-rpath,.

// ./main