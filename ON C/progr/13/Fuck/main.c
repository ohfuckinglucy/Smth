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
   

    for (int n = 100; n <= 500; n+= 100){
    int choise;
    printf(RED "Просим не заполнять массив элементами свыше 500 во избежании ошибок!!!\n" RESET);

    int massive[n];
    int cmassive[n];
    int smassive[n];
    int imassive[n];


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
            printf(RED "Я же просил меньше 500. . .\n" RESET);
            continue;
        }
    

        printf(CYAN "Каким методом будем сортировать массив?: \n" RESET);
        printf(GREEN "1 - BinaryInsertionSort.\n" RESET);
        printf(MAGENTA "2 - InsertionSort.\n" RESET);
        printf(BLUE "3 - ShellSort.\n" RESET);



        scanf("%d", &choise);

        // printf(YELLOW "До сортировки\n"RESET);
        // showmas(massive, n);

        printf(YELLOW "\nМетод сортировки\tКоличество элементов\tКоличество пересылок\tКоличество сравнений\n" RESET);

        int resultofarr = ChooseSort(massive, n, choise);

        if (resultofarr == 1){
            printf(CYAN "BinaryInsertionSort\t\t%d\t\t\t%d\t\t\t%d\n" RESET, n, swapsBubble, comparisonsBubble);
        }else if (resultofarr == 2){
            printf(BLUE "InsertionSort\t\t%d\t\t\t%d\t\t\t%d\n" RESET, n, swapsInsertion, comparisonsInsertion);
        }else if (resultofarr == 3){
            printf(GREEN "ShellSort\t\t%d\t\t\t%d\t\t\t%d\n" RESET, n, swapsShell, comparisonsShell);
        }else if (resultofarr == 4){
            printf(MAGENTA "CountingSort\t\t%d\t\t\t%d\t\t\t%d\n" RESET, n, swapsCounting, comparisonsCounting);
        }

        // printf(YELLOW "\n\nПосле сортировки\n"RESET);
        // showmas(massive, n);



        break;
    }
    }
}