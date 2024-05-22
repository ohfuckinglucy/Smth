#include<iostream>
#include<string>
using namespace std;

class phone{
private:
    string OS;
    int OSVER;
    string TypeOfData;


public:
    phone (string OS,int O, string TOF){
    OS=OS;
    OSVER=O;
    TypeOfData=TOF;
}

void outputTo() {
    cout<<"Операционная система телефона: "<<OS<<endl;
    cout<<"Версия операционной системы: "<<OSVER<<endl;
    cout<<"Вид интернет соединения: "<<TypeOfData<<endl;
}

string get_OS() {
    return OS;
}

void set_OSVER(int a) {
    OSVER = a;
}

string get_TypeOfData(){
    return TypeOfData;
}

};

int main(){
    phone *samsung_galaxy_s_3 = new phone("Android", 4, "Wi-Fi and 3G");
    phone *iphone_5 = new phone("IOS",11, "Wi-Fi and 4G");

    samsung_galaxy_s_3->outputTo();
    iphone_5->outputTo();

    samsung_galaxy_s_3->set_OSVER(5);
    iphone_5->set_OSVER(12);

    samsung_galaxy_s_3->outputTo();
    iphone_5->outputTo();

    return 0;
}