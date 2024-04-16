#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    char str[20];

    srand(time(NULL));

    for (int i = 0; i < 20; i ++){
        str[i] = rand() * 1.0 / (123-98) + 98;
        if (i == 19){
            str[i] = '\0';
        }
        printf("%c", str[i]);
    }
}