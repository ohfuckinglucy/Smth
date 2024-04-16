#include <stdio.h>
#include <stdlib.h>

int Get5(){
    return 5;
}

int main(){
    int (*func)();

    printf("%d\n", Get5());
}