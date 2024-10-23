#include <stdio.h>

int main(){
    char str[8];
    for(int i = 0; i < 8; i++){
        str[i] = '#';
    }
    printf("%s\n", str);
    for(int i = 0;; i++){
        printf("%c", str[i]);
        if (str[i] == '\0'){
            break;
        }
    }
}