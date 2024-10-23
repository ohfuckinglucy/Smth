#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>

using namespace std;

class Triangle {
protected:
    double a, b, c;

    bool isTriangle() const {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }

public:
    Triangle(double side1, double side2, double side3) : a(side1), b(side2), c(side3) {
        if (!isTriangle()) {
            throw invalid_argument("Неверные стороны для треугольника");
        }
    }

    double getPerimeter() const {
        return a + b + c;
    }

    double getArea() const {
        double s = getPerimeter() / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    void getAngles(double &angleA, double &angleB, double &angleC) const {
        angleA = acos((b*b + c*c - a*a) / (2 * b * c)) * 180.0 / M_PI;
        angleB = acos((a*a + c*c - b*b) / (2 * a * c)) * 180.0 / M_PI;
        angleC = acos((a*a + b*b - c*c) / (2 * a * b)) * 180.0 / M_PI;
    }

    void printInfo() const {
        cout << "Стороны треугольника: a=" << a << ", b=" << b << ", c=" << c << endl;
        cout << "Периметр: " << getPerimeter() << endl;
        cout << "Площадь: " << getArea() << endl;

        double angleA, angleB, angleC;
        getAngles(angleA, angleB, angleC);
        cout << "Углы: A=" << angleA << ", B=" << angleB << ", C=" << angleC << endl;
    }
};

class Prism : public Triangle {
private:
    double height;

public:
    Prism(double side1, double side2, double side3, double height) 
        : Triangle(side1, side2, side3), height(height) {
        if (height <= 0) {
            throw invalid_argument("Неверная высота для призмы");
        }
    }

    double getVolume() const {
        return getArea() * height;
    }

    double getSurfaceArea() const {
        double baseArea = getArea();
        double lateralSurfaceArea = getPerimeter() * height;
        return 2 * baseArea + lateralSurfaceArea;
    }

    void printInfo() const {
        Triangle::printInfo();
        cout << "Высота: " << height << endl;
        cout << "Объем: " << getVolume() << endl;
        cout << "Площадь поверхности: " << getSurfaceArea() << endl;
    }
};

int main() {
    int numTriangles;
    cout << "Введите количество треугольников для создания: ";
    cin >> numTriangles;

    vector<Triangle> triangles;
    vector<Prism> prisms;

    for (int i = 0; i < numTriangles; ++i) {
        double side1, side2, side3, height;
        cout << "Введите стороны треугольника " << i + 1 << ": ";
        cin >> side1 >> side2 >> side3;
        
        try {
            Triangle t(side1, side2, side3);
            triangles.push_back(t);

            cout << "Введите высоту призмы " << i + 1 << ": ";
            cin >> height;
            Prism p(side1, side2, side3, height);
            prisms.push_back(p);
        } catch (const invalid_argument &e) {
            cerr << e.what() << endl;
        }
    }

    cout << "\nИнформация о треугольниках:\n";
    for (const auto& t : triangles) {
        t.printInfo();
        cout << endl;
    }

    cout << "\nИнформация о призмах:\n";
    for (const auto& p : prisms) {
        p.printInfo();
        cout << endl;
    }

    return 0;
}
