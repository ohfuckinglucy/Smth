#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;

class Triangle {
protected:
    double a, b, c;

public:
    Triangle(double side1, double side2, double side3)
        : a(side1), b(side2), c(side3) {}

    bool exists() const {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }

    double perimeter() const {
        return a + b + c;
    }

    double area() const {
        double s = perimeter() / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    void displayInfo() const {
        cout << "Стороны: a = " << a << ", b = " << b << ", c = " << c << endl;
        if (exists()) {
            cout << "Периметр: " << perimeter() << endl;
            cout << "Площадь: " << area() << endl;
        } else {
            cout << "Треугольник не существует." << endl;
        }
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(double side1, double side2, double side3)
        : Triangle(side1, side2, side3) {}

    bool isIsosceles() const {
        return (a == b) || (a == c) || (b == c);
    }

    void displayInfo() const {
        Triangle::displayInfo();
        if (isIsosceles()) {
            cout << "Это равнобедренный треугольник." << endl;
        } else {
            cout << "Это не равнобедренный треугольник." << endl;
        }
    }
};

int main() {
    int n, m;

    cout << "Введите количество треугольников: ";
    cin >> n;

    vector<Triangle> triangles;
    for (int i = 0; i < n; ++i) {
        double a, b, c;
        cout << "Введите стороны треугольника " << i + 1 << " (a, b, c): ";
        cin >> a >> b >> c;
        triangles.push_back(Triangle(a, b, c));
    }

    cout << "Введите количество равнобедренных треугольников: ";
    cin >> m;

    vector<IsoscelesTriangle> isoscelesTriangles;
    for (int i = 0; i < m; ++i) {
        double a, b, c;
        cout << "Введите стороны равнобедренного треугольника " << i + 1 << " (a, b, c): ";
        cin >> a >> b >> c;
        isoscelesTriangles.push_back(IsoscelesTriangle(a, b, c));
    }

    double totalArea = 0.0;
    for (const auto& tri : triangles) {
        if (tri.exists()) {
            totalArea += tri.area();
        }
    }
    double averageArea = totalArea / triangles.size();
    cout << "Средняя площадь треугольников: " << averageArea << endl;

    double minIsoscelesArea = numeric_limits<double>::max();
    IsoscelesTriangle* minAreaTriangle = nullptr;
    for (auto& isoTri : isoscelesTriangles) {
        if (isoTri.exists() && isoTri.isIsosceles()) {
            double area = isoTri.area();
            if (area < minIsoscelesArea) {
                minIsoscelesArea = area;
                minAreaTriangle = &isoTri;
            }
        }
    }

    if (minAreaTriangle) {
        cout << "Равнобедренный треугольник с наименьшей площадью: " << endl;
        minAreaTriangle->displayInfo();
    } else {
        cout << "Равнобедренные треугольники не найдены." << endl;
    }

    return 0;
}
