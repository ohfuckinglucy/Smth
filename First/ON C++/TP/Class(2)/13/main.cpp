#include <iostream>
#include <string>

using namespace std;

// Суперкласс - Места развлечений
class EntertainmentPlace {
private:
    string institutionType;
    int capacity;

public:
    // Конструктор для инициализации значений полей объекта
    EntertainmentPlace(const string& type, int cap) 
        : institutionType(type), capacity(cap) {}

    // Методы для изменения значений полей объекта
    void setInstitutionType(const string& type) {
        institutionType = type;
    }

    void setCapacity(int cap) {
        capacity = cap;
    }

    // Методы для получения значений полей объекта
    string getInstitutionType() const {
        return institutionType;
    }

    int getCapacity() const {
        return capacity;
    }

    // Метод для вывода всей имеющейся информации об объекте
    void displayInfo() const {
        cout << "Тип учреждения: " << institutionType << endl;
        cout << "Вместимость: " << capacity << endl;
    }
};

// Главная функция для демонстрации работы всех методов
int main() {
    // Создание объекта класса EntertainmentPlace
    EntertainmentPlace place("Театр", 500);

    // Вывод информации об объекте до изменения
    cout << "Начальное состояние объекта:" << endl;
    place.displayInfo();
    cout << endl;

    // Изменение значений полей объекта
    place.setInstitutionType("Выставка");
    place.setCapacity(300);

    // Вывод информации об объекте после изменения
    cout << "Состояние объекта после изменений:" << endl;
    place.displayInfo();

    return 0;
}
