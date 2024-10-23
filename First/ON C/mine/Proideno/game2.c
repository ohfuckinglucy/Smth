#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#define w 65
#define h 25
#define M_PI 3.14159265358979323846

typedef struct{
    int x, y;
    int z;
} TRacket;

typedef struct{
    float x, y;
    int ix, iy;
    float alfa;
    float speed;
} TBall;

TRacket racket;
TBall ball;
char mas[h][w + 1];
int hitCnt = 0;
int maxHitCnt = 0;
int lvl = 1;

void setcur(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void initRacket(){
    racket.z = 7;
    racket.x = ((w - racket.z) / 2);
    racket.y = h - 1;
}

void putRacket(){
    for (int i = racket.x; i < racket.x + racket.z; i++){
        mas[racket.y][i] = '@';
    }
}

void init(){
    printf("lvl %d\n", lvl);
    if (hitCnt >= 6){
            lvl = 2;
        }
    else lvl = 1;

    for (int i = 0; i < w; i ++){
        mas[0][i] = '#';
    }
    mas[0][w] = '\0';



    strncpy(mas[1], mas[0], w + 1);
    for (int i = 1; i < w-1; i ++){
        mas[1][i] = ' ';
    }

    
    for (int i = 2; i < h; i ++){
        strncpy(mas[i], mas[1], w + 1);
    }
    for (int i = 20; i < 50; i ++){
        strncpy(mas[i], mas[1], w + 1);
    }
}

void show(){
    for (int i = 0; i < h; i ++){
        printf("%s", mas[i]);
        if (i == 3){
            printf("   hit %i   ", hitCnt);
        }
        
        if (i == 4){
            printf("   max %i   ", maxHitCnt);
        }
        if (i < h - 1){
            printf("\n");
        }
    }
}
void moveRacket(int x){
    racket.x = x;
    if (racket.x < 1) racket.x = 1;
    if (racket.x + racket.z >= w) racket.x = w - 1 - racket.z;
}

void initBall(){
    moveBall(2,2);
    ball.alfa = -1;
    ball.speed = 0.5;
}

void putBall(){
    mas[ball.iy][ball.ix] = '*';
}

void moveBall(float x, float y){
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void autoMoveBall(){
    if (ball.alfa < 0) ball.alfa += M_PI*2;
    if (ball.alfa > M_PI*2) ball.alfa -= M_PI*2;

    TBall b1 = ball;

    moveBall(ball.x + cos(ball.alfa) * ball.speed,
    ball.y + sin(ball.alfa) * ball.speed);

    if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '@')){
        if (mas[ball.iy][ball.ix] == '@'){
            hitCnt++;
        }
        if ((ball.ix != b1.ix) && (ball.iy != b1.iy)){
            if (mas[b1.iy][ball.ix] == mas[ball.iy][b1.ix]){
                b1.alfa = b1.alfa + M_PI;
            }
            else{
                if (mas[b1.iy][ball.ix] == '#'){
                    b1.alfa = (2*M_PI - b1.alfa) + M_PI;
                }
                else{
                    b1.alfa = (2*M_PI - b1.alfa);
                }
            }
        }
        else if (ball.iy == b1.iy){
            b1.alfa = (2*M_PI - b1.alfa) + M_PI;
        }
        else{
            b1.alfa = (2*M_PI - b1.alfa);
        }
        ball = b1;
        autoMoveBall();
    }
}

int main(){
    char c;
    BOOL run = FALSE;
    initRacket();
    initBall();

    do{
        setcur(0,0);

        if (run){
            autoMoveBall();
        }
        if (ball.iy > h){
            run = FALSE;
            if (hitCnt > maxHitCnt){
                maxHitCnt = hitCnt;
            hitCnt = 0;
            }
        }
        init();
        putRacket();
        putBall();
        show();

        if (GetKeyState('A') < 0) moveRacket(racket.x - 1);
        if (GetKeyState('D') < 0) moveRacket(racket.x + 1);
        if (GetKeyState('W') < 0) run = TRUE;
        if (!run){
            moveBall(racket.x + racket.z / 2, racket.y - 1);
        }
        Sleep(10);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);
}