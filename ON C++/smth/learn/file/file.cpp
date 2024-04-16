#include <iostream>

using namespace std;


int main(){
    FILE *f;
    char c[1000];

    f = fopen("001.txt", "w");
        fprintf(f, "%s", "I love u bebra!!!<3\n");
        fprintf(f, "%s", "Every day!!!11!*^^<3\n");

    fclose(f);

    f = fopen("001.txt", "r");
        while (!feof(f)){
            if (fgets(c, sizeof(c), f) != NULL){
                cout << c << endl;
            }
        }

    fclose(f);
}