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
        std::cout << "Длина стороны квадрата: " << side_length << std::endl;
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
        std::cout << "Обьем призмы: " << calculateVolume() << std::endl;
    }
};

int main() {
    double sideLength, height;

    std::cout << "Введите длину стороны квадрата: ";
    std::cin >> sideLength;

    Square square(sideLength);
    square.displayInfo();

    std::cout << "\nВведите длину стороны призмы: ";
    std::cin >> sideLength;

    std::cout << "Введите высоту призмы: ";
    std::cin >> height;

    Prism prism(sideLength, height);
    prism.displayInfo();

    return 0;
}