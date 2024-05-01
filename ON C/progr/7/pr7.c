//          Задана матрица целых чисел A(n,n). Вывести номера столбцов, в которых
//          находится более двух простых чисел. Найти сумму положительных элементов матрицы.

#include <stdio.h>
#include <stdlib.h>

int main(){
    int h,w,k,sum;
    k=0;
    sum = 0;
    scanf("%d",&h); // столбцы
    scanf("%d",&w); // строки
    int m[h][w];
    
    for(int i = 0; i<h; i++){
        for(int j = 0; j<w; j++){
//              scanf("%d",&m[i][j]);
            m[i][j] = rand()%50;
        }
    }
    for(int i = 0; i<h; i++){
        for(int j = 0; j<w; j++){
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i<h; i++){
        for(int j = 0; j<w; j++){
            if(m[i][j]>0){
                sum += m[i][j];
            }
        }
    }
    printf("сумма: %d\n", sum);
    
    printf("столбцы\n");
    for(int i = 0; i<h; i++){
        k = 0;
        for(int j = 0; j<w; j++){
            if(m[i][j] % 2 != 0 && m[i][j] % 1 == 0 && m[i][j] % m[i][j] == 0 && m[i][j] != 0){
                k += 1;
            if(k >= 2){
                printf("%d\n", i);
            }
            }
        }
    }
}
