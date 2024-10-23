#include <stdlib.h>
#include <stdio.h>
#include "header.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

int main(){
    int comparisonsShell = 0, swapsShell = 0;
    int comparisonsInsertion = 0, swapsInsertion = 0;
    int comparisonsBubble = 0, swapsBubble = 0;
    int comparisonsCounting = 0, swapsCounting = 0;

    int n;
    int choise;
    printf(CYAN "Введите размерность массива: " RESET);
    scanf("%d", &n);
    int massive[n];
    int cmassive[n];
    int smassive[n];
    int imassive[n];

    printf(RED "Просим не заполнять массив элементами свыше 100 во избежании ошибок!!!\n" RESET);

    while(1){
        printf(CYAN "Каким образом будем заполнять массив?: \n" RESET);
        printf(GREEN "1 - С клавиатуры.\n" RESET);
        printf(MAGENTA "2 - Псвевдослучайными числами в промежутке от 0 до 100.\n" RESET);
        printf(BLUE "3 - Из файла.\n" RESET);
        scanf("%d", &choise);

        int result = TypeOfCompletion(choise, n, massive, cmassive, smassive, imassive);
        if (result == 0){
            printf(RED "Выберите один из предложенных методов, введя одну из предложенных цифр!\n" RESET);
            continue;
        } else if(result == 1){
            printf(RED "Не удалось открыть файл.\nВыберите другой метод или убедитесь в начилии файла." RESET);
            continue;
        } else if(result == 666){
            printf(RED "Я же просил меньше 100. . .\n" RESET);
            continue;
        }
        printf(YELLOW "До сортировки\n"RESET);
        showmas(massive, n);

        ShellSort(smassive, n, &comparisonsShell, &swapsShell);
        // printf(GREEN"Comparisons (ShellSort): %d\n"RESET, comparisonsShell);
        // printf(GREEN"Swaps (ShellSort): %d\n"RESET, swapsShell);

        insertionSort(imassive, n, &comparisonsInsertion, &swapsInsertion);
        // printf(BLUE"Comparisons (InsertionSort): %d\n"RESET, comparisonsInsertion);
        // printf(BLUE"Swaps (InsertionSort): %d\n"RESET, swapsInsertion);

        CountingSort(cmassive, n, 100, &comparisonsCounting, &swapsCounting);
        // printf(MAGENTA"Comparisons (CountingSort): %d\n"RESET, comparisonsCounting);
        // printf(MAGENTA"Swaps (CountingSort): %d\n"RESET, swapsCounting);

        BubbleSort(massive, n, &comparisonsBubble, &swapsBubble);
        // printf(CYAN"Comparisons (BubbleSort): %d\n"RESET, comparisonsBubble);
        // printf(CYAN"Swaps (BubbleSort): %d\n"RESET, swapsBubble);

        printf(YELLOW "\nМетод сортировки\tКоличество элементов\tКоличество пересылок\tКоличество сравнений\n" RESET);

        printf(GREEN "ShellSort\t\t%d\t\t\t%d\t\t\t%d\n" RESET, n, swapsShell, comparisonsShell);

        printf(BLUE "InsertionSort\t\t%d\t\t\t%d\t\t\t%d\n" RESET, n, swapsInsertion, comparisonsInsertion);

        printf(MAGENTA "CountingSort\t\t%d\t\t\t%d\t\t\t%d\n" RESET, n, swapsCounting, comparisonsCounting);

        printf(CYAN "BubbleSort\t\t%d\t\t\t%d\t\t\t%d\n" RESET, n, swapsBubble, comparisonsBubble);

        printf(YELLOW "После сортировки\n"RESET);
        showmas(massive, n);



        break;
    }
}