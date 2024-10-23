#include <stdio.h>
#include <stdlib.h>

struct TPoint{
    int x;
    int y;
};

typedef struct TPoint Point;

void SetPoint(Point *point, int xpos, int ypos){
    (*point).x = xpos;
    (*point).y = ypos;
}

void ShowPoint(Point *pt){
    printf("x = %d\ny = %d\n", (*pt).x,(*pt).y);
}

int main(){
    Point p;
    int x, y;
    Point *pt = NULL;
    pt = &p;
    scanf("%d %d", &x, &y);
    SetPoint(pt, x, y);
    ShowPoint(pt);
}