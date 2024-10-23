// ТЕМА 8. Строки, использование стандартных функций для обработки строк. Типы данных, определяемые пользователем
// Вывести символы, которые встречаются в исходном  предложении по одному разу.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 256

char ramd_let(){
    return 'A' + rand() % 26;
}
int main(){
    srand(time(NULL));
    char sent[1000];
    int len = rand() % 101;
    for(int k = 0; k < len; k ++){
        sent[k] = ramd_let();
    }
    for(int i = 0; i < len; i++){
        char curChar = sent[i];
        int count = 0;
     
        for(int j = 0; j < len; j ++){
            if(sent[j] == curChar){
                count++;
            }
        }
            if(count == 1){
                printf("%d %c\n", i, curChar);
            }
    }
} 


int main(){
    char str[100];
    
    int freq[MAX_SIZE] = {0};
    
    char endstart[] = " ";
    
    printf("Введите предложение: \n");
    
    char *token;
    int count = 0;
    
    fgets(str, sizeof(str), stdin);
    
    token = strtok(str, endstart);
    token = strtok(NULL, endstart);
    
    strcpy(str, token);
    

    
    int len = strlen(str);
    
    for(int i = 0; i < len; i++){
        if (str[i] != ' '){
            freq[(int)str[i]]++;
        }
    }
    printf("Символы встречающиеся один раз: \n");
    for (int i = 0; i < MAX_SIZE; i++){
        if (freq[i] == 1){
            printf("%c  ",i);
        }
    }
    return 0;
}
