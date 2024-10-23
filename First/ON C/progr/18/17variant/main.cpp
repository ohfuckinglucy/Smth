#include <iostream>
#include <vector>
#include <string>

// Класс для хранения информации о мобильных телефонах
class MobilePhone {
public:
    std::string model;
    int releaseYear;

    MobilePhone(std::string m, int y) : model(m), releaseYear(y) {}
};

// Функция для добавления телефона в вектор, если год выпуска после 2019
void addPhoneIfRecent(std::vector<MobilePhone>& phones, const MobilePhone& phone) {
    if (phone.releaseYear > 2019) {
        phones.push_back(phone);
    }
}

// Функция для вывода информации о телефонах
void displayPhones(const std::vector<MobilePhone>& phones) {
    for (const auto& phone : phones) {
        std::cout << "Model: " << phone.model << ", Release Year: " << phone.releaseYear << std::endl;
    }
}

int main() {
    // Вектор для хранения всех телефонов
    std::vector<MobilePhone> allPhones = {
        MobilePhone("iPhone 11", 2019),
        MobilePhone("Samsung Galaxy S20", 2020),
        MobilePhone("Samsung galaxy s 3", 2012),
        MobilePhone("OnePlus 8", 2020),
        MobilePhone("Google Pixel 5", 2020),
        MobilePhone("sony xperia c3 dual", 2014),
        MobilePhone("iPhone 12", 2020),
        MobilePhone("Samsung Galaxy S21", 2021),
        MobilePhone("OnePlus 9", 2021),
        MobilePhone("Nokia lumia 1020", 2013),
        MobilePhone("Google Pixel 6", 2021),
        MobilePhone("iPhone 13", 2021),
        MobilePhone("Samsung Galaxy S22", 2022),
        MobilePhone("OnePlus 10", 2022),
        MobilePhone("Nokia 1110", 2005),
        MobilePhone("Google Pixel 7", 2022)
    };

    // Вектор для хранения телефонов, выпущенных после 2019 года
    std::vector<MobilePhone> recentPhones;

    // Добавляем телефоны в вектор recentPhones, если год выпуска после 2019
    for (const auto& phone : allPhones) {
        addPhoneIfRecent(recentPhones, phone);
    }

    // Выводим информацию о телефонах, выпущенных после 2019 года
    std::cout << "Phones released after 2019:" << std::endl;
    displayPhones(recentPhones);

    return 0;
}
