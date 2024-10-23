#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Класс для представления монитора
class Monitor {
public:
    string model; // Модель монитора
    int width;    // Ширина разрешения
    int height;   // Высота разрешения

    // Конструктор для инициализации полей класса
    Monitor(const string &model, int width, int height)
        : model(model), width(width), height(height) {}

    // Метод для проверки, является ли разрешение монитора высоким
    bool isHighResolution() const {
        return width >= 1920 && height >= 1080; // Full HD или выше
    }
};

// Класс для хранения и управления мониторами с высоким разрешением
class HighResolutionMonitors {
private:
    vector<Monitor> monitors; // Вектор для хранения мониторов

public:
    // Метод для добавления монитора в вектор, если разрешение высокое
    void addMonitor(const Monitor &monitor) {
        if (monitor.isHighResolution()) {
            monitors.push_back(monitor);
        }
    }

    // Метод для вывода списка мониторов с высоким разрешением
    void printMonitors() const {
        for (const auto &monitor : monitors) {
            cout << "Model: " << monitor.model 
                 << ", Resolution: " << monitor.width << "x" << monitor.height << endl;
        }
    }
};

int main() {
    // Создание объектов мониторов с различными разрешениями
    Monitor m1("Model A", 1920, 1080);
    Monitor m2("Model B", 1366, 768);
    Monitor m3("Model C", 2560, 1440);
    Monitor m4("Model D", 3840, 2160);

    // Создание объекта для хранения мониторов с высоким разрешением
    HighResolutionMonitors highResMonitors;
    highResMonitors.addMonitor(m1); // Добавление первого монитора
    highResMonitors.addMonitor(m2); // Добавление второго монитора
    highResMonitors.addMonitor(m3); // Добавление третьего монитора
    highResMonitors.addMonitor(m4); // Добавление четвертого монитора

    // Вывод списка мониторов с высоким разрешением
    cout << "High Resolution Monitors:" << endl;
    highResMonitors.printMonitors();

    return 0; // Завершение программы
}
