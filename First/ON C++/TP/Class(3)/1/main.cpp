#include <iostream>
#include <cmath>

using namespace std;

class square{
    private:
        int len;
    public:
        square(int len){
            this->len = len;
        }

        double getdiagonal(){
            return len * sqrt(2);
        }
        double getperimetr(){
            return len * 4;
        }
        double getarea(){
            return len*len;
        }

        void displayinfo(){
            cout << "Сторона квадрата: " << len << endl;
            cout << "Диагональ квадрата: " << getdiagonal() << endl;
            cout << "Периметр квадрата: " << getperimetr() << endl;
            cout << "Площадь квадрата " << getarea() << endl;
        }
};

class sqprism : square{
    private:
        int height;
    public:
        sqprism(int len, int height) : square(len){
            this -> height = height;
        }
        double getvolume(){
            return getarea() * height;
        }

        void displayinfo(){
            square::displayinfo();
            cout << "Объем призмы: " << getvolume() << endl;
        }
};

int main(){
    square *KV1 = new square(5);
    sqprism *KV2 = new sqprism(2, 4);

    KV1->displayinfo();
    KV2->displayinfo();
}