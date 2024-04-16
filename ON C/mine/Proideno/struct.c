#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sofa{
    int xap[3];
    char name[50];
    char color[15];
} s;


int main(){
    struct Sofa a[3];
    

    s.xap[0] = 100;
    s.xap[1] = 60;
    s.xap[2] = 100;
    strcpy(s.name, "sofa");
    strcpy(s.color, "orange");

    for (int i = 0; i < 3; i ++){
        for (int j = 0; j < 3; j ++){
            a[i].xap[j] = s.xap[j];
            strcpy(a[i].name, s.name);
            strcpy(a[i].color, s.color);

        }
    }

    for(int i = 0; i < 3; i ++){
        printf("%d", a[i].xap[i]);
        printf("%s", a[i].name);
    }
}