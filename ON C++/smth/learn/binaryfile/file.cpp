#include <iostream>

using namespace std;

int main(){
    FILE *f;

    int i = 7;

    f = fopen("file.txt", "w");
        fwrite(&i, 1, sizeof(i), f);
    fclose(f);

    int buf;

    f = fopen("file.txt", "r");
        fread(&buf, 1, sizeof(buf), f);
    fclose(f);

    cout << buf << endl;


}