#include <stdio.h>
#include <stdlib.h>

int Ternar(int i){
    i = (i < 10 ? 10 : (i > 100 ? 100 : (i + 1000))); 
}

int Rec(int i, int j){
    if (j > 1){
        return i * Rec(i, (j - 1));
    }
    else{
        return i;
    }
}

int main(){
    printf("%d\n", Ternar(42));
    printf("%d\n", Rec(4, 2));
}