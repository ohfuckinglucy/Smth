#include "stdio.h"

int main(void){
float x, y;
printf("Введите значение перменных\n");
scanf("%f %f", &x, &y);
if(x > 1 || y > 1){
	printf("error\n");
}
else{
	if(y >= 0){
		printf("Да, точки %.2f и %.2f принадлежат заштрихованной области\n", x, y);
	}
	if(y < 0){
		if(x >= y==-x || x >= y==x){
			printf("Да, точки %.2f и %.2f принадлежат заштрихованной области\n", x, y);
	}
		else{
			printf("Нет, точки %.2f и %.2f не принадлежат заштрихованной области\n", x, y);
}
}
}
}
