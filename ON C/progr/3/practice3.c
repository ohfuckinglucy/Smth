#include <stdio.h>

int main(){
	int s = 12;
	int w =3;

	for(int i = 0;i < s; i+=1){
	if(i == 0 || i == s-1){
	for(int j = 0; j<w;j+=1){
        printf("*");
}

	printf("\n");
}

	if(i > 0 && i < s-1){
	for(int j = 0; j<w;j+=1){
        if(j == 0 || j == w-1){
	printf("*");
}

	else printf("-");
}

	printf("\n");
}
}
}
