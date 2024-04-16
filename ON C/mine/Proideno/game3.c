#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define mapWidth 80
#define mapHeight 25

typedef struct SObject{
    float x, y;
    float h, w;
    float vertSpeed;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject brick[1];

void ClearMap(){
    for (int i = 0; i < mapWidth; i ++){
        map[0][i] = '.';
    }
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j ++){
        sprintf(map[j], map[0]);
    }
}

void ShowMap(){
    map[mapHeight-1][mapWidth - 1] = '\0';
    for (int j = 0; j < mapHeight; j ++){
        printf("%s", map[j]);
    }
}

void SetObjectPos(TObject *obj, float xPos, float yPos){
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oW, float oH){
    SetObjectPos(obj, xPos, yPos);
    (*obj).w = oW;
    (*obj).h = oH;
    (*obj).vertSpeed = 0;
}

void VertMoveOblect(TObject *obj){
    (*obj).vertSpeed += 0.05;
    SetObjectPos(obj, (*obj).x, (*obj).y * (*obj).vertSpeed);
}

void PutObjectOnMap(TObject obj){
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iW = (int)round(obj.w);
    int iH = (int)round(obj.h);
    for (int i = ix; i < (ix + iW); i ++){
        for (int j = iy; j < (iy + iH); j ++){
            if (IsPosInMap(i, j)){
                map[j][i] = '@';
            }
        }
    }
}

void setCur(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

BOOL IsPosInMap(int x, int y){
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

int main(){
    InitObject(&mario, 39, 10, 3, 3);
    do{
        ClearMap();
        VertMoveOblect(&mario);
        setCur(0, 0);
        PutObjectOnMap(mario);
        ShowMap();

        sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);
}