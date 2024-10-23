#include <stdio.h>
// 46 variant
// cravnenie elementov massiva bez pererivnoe

int main(){
    int i,s,k;
    int A[] = {1,2,2,3,4,5,3,-1};

    for (i=1,s=0,k=0; i<10; i++){
        if (A[i-1]<A[i]) k++;
        else{ 
            if (k>s) s=k;
                k=0;
        }
    }
    printf("%d %d %d\n", i, s, k);
}