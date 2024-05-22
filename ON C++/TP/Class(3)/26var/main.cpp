#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Square {
private:
    double side_length;

public:
    Square(double side_length) {
        this->side_length = side_length;
    }

    double calculateDiagonal() const {
        return side_length * sqrt(2);
    }

    double calculatePerimeter() const {
        return 4 * side_length;
    }

    double calculateArea() const {
        return side_length * side_length;
    }

    void displayInfo() const {
        cout << "Длина стороны квадрата:" << side_length << endl;
        cout << "Диагональ квадрата: " << calculateDiagonal() << endl;
        cout << "Периметр квадрата: " << calculatePerimeter() << endl;
        cout << "Площадь квадрата: " << calculateArea() << endl;
    }
};

class Prism : public Square {
private:
    double height;

public:
    Prism(double side_length, double height) : Square(side_length) {
        this->height = height;
    }

    double calculateVolume() const {
        return calculateArea() * height;
    }

    void displayInfo() const {
        Square::displayInfo();
        cout << "Высота призмы: " << height << endl;
        cout << "Объем призмы: " << calculateVolume() << endl;
    }
};

int main() {
    int N, M;

    cout << "Введите число квадратов (N): ";
    cin >> N;

    cout << "Введите число призм (M): ";
    cin >> M;

    vector<Square> squares;
    vector<Prism> prisms;

    for (int i = 1; i <= N; ++i) {
        double sideLength;
        cout << "Введите длину стороны квадрата " << i << ": ";
        cin >> sideLength;

        Square square(sideLength);
        squares.push_back(square);
    }

    for (int i = 1; i <= M; ++i) {
        double sideLength, height;
        cout << "Введите длину стороны призмы " << i << ": ";
        cin >> sideLength;

        cout << "Введите высоту призмы " << i << ": ";
        cin >> height;

        Prism prism(sideLength, height);
        prisms.push_back(prism);
    }

    double max_area = 0;
    Square max_square(0);

    for (const auto& square : squares) {
        if (square.calculateArea() > max_area) {
            max_area = square.calculateArea();
            max_square = square;
        }
    }

    double max_volume = 0;
    Prism max_prism(0, 0);

    for (const auto& prism : prisms) {
        if (prism.calculateVolume() > max_volume) {
            max_volume = prism.calculateVolume();
            max_prism = prism;
        }
    }

    cout << "\nКвадрат с максимальной площадью:" << endl;
    max_square.displayInfo();

    cout << "\nПризма с максимальной площадью:" << endl;
    max_prism.displayInfo();

    return 0;
}
