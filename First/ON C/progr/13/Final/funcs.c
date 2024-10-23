#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "header.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

int TypeOfCompletion(int choise, int n, int arr[], int arr2[], int arr3[], int arr4[]){
    switch (choise)
    {
    case 1:
        printf(CYAN "Вводите числа\nКол-во числе в массиве %d\n" RESET, n);
        int num;
        
        for (int i = 0; i < n; i ++){
            scanf("%d", &num);
            if (num > 500){
            return 666;
        }
            arr[i] = arr2[i] = arr3[i] = arr4[i] = num;
        }
        return 10;

    case 2:
        srand(time(NULL));
        for (int i = 0; i < n; i ++){
            arr[i] = arr2[i] = arr3[i] = arr4[i] = rand() % 100;
        }
        return 10;

    case 3: 
        FILE *file = fopen("numbers.txt", "r");
        if (file == NULL){
            return 1;
        }
        else{
            for (int i = 0; i < n; i ++){
                fscanf(file, "%d", &arr[i]);
                arr[i] = arr2[i] = arr3[i] = arr4[i];
            }
            fclose(file);
        }
        return 10;

    default:
        return 0;
    }
}

void showmas(int arr[], int n){
    printf(CYAN "Ваш массив: " RESET);
    for (int i = 0; i < n; i ++){
        printf(YELLOW "%d " RESET, arr[i]);
        if (i % 40 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

int ChooseSort(int arr[], int n, int choose){
    switch (choose)
    {
    case 1:
        BubbleSort(arr, n, &comparisonsBubble, &swapsBubble);
        return 1;

    case 2:
        insertionSort(arr, n, &comparisonsInsertion, &swapsInsertion);
        return 2;

    case 3:
        ShellSort(arr, n, &comparisonsShell, &swapsShell);
        return 3;

    case 4:
        CountingSort(arr, n, &comparisonsCounting, &swapsCounting);
        return 4;

    default:
        return 0;
    }
}