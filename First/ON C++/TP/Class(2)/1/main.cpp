#include <iostream>
#include <string>
#include <vector>

using namespace std;

class computer{
    private:
        string type;
        int ram;
    public:
        computer(string type, int ram){
            this->type = type;
            this->ram = ram;
        }

        void setram(int ram){
            this->ram = ram;
        }

        void settype(string type){
            this->type = type;
        }

        int getram(){
            return ram;
        }

        string gettype(){
            return type;
        }

        void displayinfo(){
            cout << "Модель процессора: " << type << endl;
            cout << "Кол-во ОЗУ: " << ram << endl;
            cout << endl;
        }
};

int main(){
    computer *One = new computer("AMD", 8);
    computer *Two = new computer("INTEL", 32);
    computer *Three = new computer("INTEL", 4);

    One->displayinfo();
    Two->displayinfo();
    Three->displayinfo();

    Two->setram(8);
    Two->settype("AMD");

    One->displayinfo();
    Two->displayinfo();
    Three->displayinfo();
}