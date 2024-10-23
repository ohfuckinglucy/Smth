#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define GK 3

char key;

struct User{
    char name[15];
    int money, old;
    int win, lose;
} User;

struct Games{
    char gname[15];
    int price[5];
    int itog;
}Game[GK];

void Reg(){
    do{
        printf("Your name?\n");
        scanf("%s", &User.name);
        if ((User.name == "Arina") || (User.name == "arina")){
            printf("I luv u, my sweatty! <3\n");
        }

        printf("How are u old?\n");
        scanf("%d", &User.old);
        if (User.old < 18){
            printf("Sorry, u should leave this programm.\n");
            getch();
            break;
        }
        printf("Your name is: %s and your old: %d\nRight?\nPress Y for yes and N for no.\n", User.name, User.old);
        key = getch();
        if (key == 'y'){
            printf("Okay, Let's Play!\n");
        }
        if (key == 'n'){
            printf("So... Again?\n");
            continue;
        }
        if (key != 'n' && key != 'y') {
            printf("Try again.\n");
            continue;
        }
        printf("Are u ready?");
        key == getch();
        if (key == 'y'){
            break;
        }
    }
    while(key != 'e');
}

void gameListInit(){
    for (int i = 0; i < GK; i++){
        for (int j = 0; j < 15; j ++){
            sprintf(Game[i].gname, "777");
        }
    }
}

void gameList(){
    printf("");
}

int main(){
    Reg();
}