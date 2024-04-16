#include <iostream>
#include <vector>
#include <cmath>

class Square {
private:
    double side_length;

public:
    Square(double side_length) {
        this->side_length = side_length;
    }

    double calculateDiagonal() const {
        return side_length * std::sqrt(2);
    }

    double calculatePerimeter() const {
        return 4 * side_length;
    }

    double calculateArea() const {
        return side_length * side_length;
    }

    void displayInfo() const {
        std::cout << "Длина стороны квадрата:" << side_length << std::endl;
        std::cout << "Диагональ квадрата: " << calculateDiagonal() << std::endl;
        std::cout << "Периметр квадрата: " << calculatePerimeter() << std::endl;
        std::cout << "Площадь квадрата: " << calculateArea() << std::endl;
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
        std::cout << "Высота призмы: " << height << std::endl;
        std::cout << "Объем призмы: " << calculateVolume() << std::endl;
    }
};

int main() {
    int N, M;

    std::cout << "Введите число квадратов (N): ";
    std::cin >> N;

    std::cout << "Введите число призм (M): ";
    std::cin >> M;

    std::vector<Square> squares;
    std::vector<Prism> prisms;

    for (int i = 1; i <= N; ++i) {
        double sideLength;
        std::cout << "Введите длину стороны квадрата " << i << ": ";
        std::cin >> sideLength;

        Square square(sideLength);
        squares.push_back(square);
    }

    for (int i = 1; i <= M; ++i) {
        double sideLength, height;
        std::cout << "Введите длину стороны призмы " << i << ": ";
        std::cin >> sideLength;

        std::cout << "Введите высоту призмы " << i << ": ";
        std::cin >> height;

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

    std::cout << "\nКвадрат с максимальной площадью:" << std::endl;
    max_square.displayInfo();

    std::cout << "\nПризма с максимальной площадью:" << std::endl;
    max_prism.displayInfo();

    return 0;
}
