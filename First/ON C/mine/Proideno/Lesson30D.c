#include <stdio.h>
#include <stdlib.h>

typedef float (*TFUNK)(float, float);

float aplusb(float a, float b){
    return (a + b);
}

float axb(float a, float b){
    return(a * b);
}

int main(){
    TFUNK func[2];
    func[0] = aplusb;
    func[1] = axb;

    printf("%f\n%f\n", func[0](4.12, 8.21341), func[1](4.12, 8.21341));
}