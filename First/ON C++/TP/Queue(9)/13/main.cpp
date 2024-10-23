#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Структура для хранения информации о заявке
struct TicketRequest {
    string destination;
    string flightNumber;
    string passengerName;
    string flightDate;

    // Конструктор для удобного создания заявок
    TicketRequest(string dest, string flightNo, string name, string date)
        : destination(dest), flightNumber(flightNo), passengerName(name), flightDate(date) {}
};

// Функция для вывода всех заявок в очереди
void printQueue(queue<TicketRequest> q) {
    while (!q.empty()) {
        TicketRequest request = q.front();
        q.pop();
        cout << "Пункт назначения: " << request.destination << endl;
        cout << "Номер рейса: " << request.flightNumber << endl;
        cout << "Фамилия и инициалы пассажира: " << request.passengerName << endl;
        cout << "Желаемая дата вылета: " << request.flightDate << endl;
        cout << "------------------------------" << endl;
    }
}

int main() {
    queue<TicketRequest> ticketQueue;
    int choice;

    do {
        cout << "Меню:" << endl;
        cout << "1. Добавить заявку" << endl;
        cout << "2. Удалить заявку" << endl;
        cout << "3. Вывести все заявки" << endl;
        cout << "4. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(); // Игнорируем символ новой строки после выбора действия

        switch (choice) {
        case 1: {
            // Добавление заявки
            string destination, flightNumber, passengerName, flightDate;
            cout << "Введите пункт назначения: ";
            getline(cin, destination);
            cout << "Введите номер рейса: ";
            getline(cin, flightNumber);
            cout << "Введите фамилию и инициалы пассажира: ";
            getline(cin, passengerName);
            cout << "Введите желаемую дату вылета: ";
            getline(cin, flightDate);

            TicketRequest request(destination, flightNumber, passengerName, flightDate);
            ticketQueue.push(request);
            cout << "Заявка добавлена." << endl;
            break;
        }
        case 2:
            // Удаление заявки
            if (!ticketQueue.empty()) {
                ticketQueue.pop();
                cout << "Заявка удалена." << endl;
            } else {
                cout << "Очередь пуста, нет заявок для удаления." << endl;
            }
            break;
        case 3:
            // Вывод всех заявок
            if (!ticketQueue.empty()) {
                cout << "Все заявки:" << endl;
                printQueue(ticketQueue);
            } else {
                cout << "Очередь пуста." << endl;
            }
            break;
        case 4:
            // Выход
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    } while (choice != 4);

    return 0;
}
