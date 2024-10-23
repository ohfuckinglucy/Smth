#include <stdio.h>
/*
int main(){
int a, k;
int s = 0;
scanf("%d", &a);
for (int n = a; n!=0; n=n/10){
	k=n%10;
	s=s*10+k;
}
printf("s = %d, k = %d\n", s,k);
return 0;
}
*/

int main(){
int k = 0;
int m = 1;
int n;
scanf("%d",&n);
for (;m <= n;){
	k = k + 1;
	m = m * 2;
}
printf("k-1 = %d, m = %d\n",k-1,m);
return 0;
}

/*
int main(){
int a, n, k;
int s = 0;
scanf("%d", &a);
for (n=a, s=0; n!=0; n=n/10){
	k = n % 10;
	s = s + k;
}
printf("k = %d, s = %d", k, s);
}
*/
