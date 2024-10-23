#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;

class Triangle {
protected:
    struct Point {
        double x, y;
    };

    Point A, B, C;

public:
    Triangle(double ax, double ay, double bx, double by, double cx, double cy) {
        A = {ax, ay};
        B = {bx, by};
        C = {cx, cy};
    }

    bool exists() const {
        double area = abs((A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y)) / 2.0);
        return area > 0;
    }

    double sideLength(const Point &p1, const Point &p2) const {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }

    double perimeter() const {
        return sideLength(A, B) + sideLength(B, C) + sideLength(C, A);
    }

    double area() const {
        return abs((A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y)) / 2.0);
    }

    void printInfo() const {
        cout << "Треугольник: \n";
        cout << "  A(" << A.x << ", " << A.y << ")\n";
        cout << "  B(" << B.x << ", " << B.y << ")\n";
        cout << "  C(" << C.x << ", " << C.y << ")\n";
        cout << "  Периметр: " << perimeter() << "\n";
        cout << "  Площадь: " << area() << "\n";
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(double ax, double ay, double bx, double by, double cx, double cy) 
        : Triangle(ax, ay, bx, by, cx, cy) {}

    bool isRight() const {
        double a = sideLength(A, B);
        double b = sideLength(B, C);
        double c = sideLength(C, A);
        return (abs(a*a + b*b - c*c) < 1e-9 || 
                abs(b*b + c*c - a*a) < 1e-9 || 
                abs(c*c + a*a - b*b) < 1e-9);
    }

    void printInfo() const {
        cout << "Прямоугольный треугольник: \n";
        Triangle::printInfo();
        cout << "  Является прямоугольным: " << (isRight() ? "Да" : "Нет") << "\n";
    }
};

int main() {
    int N, M;
    cout << "Введите количество треугольников: ";
    cin >> N;
    cout << "Введите количество прямоугольных треугольников: ";
    cin >> M;

    vector<Triangle> triangles;
    vector<RightTriangle> rightTriangles;

    for (int i = 0; i < N; ++i) {
        double ax, ay, bx, by, cx, cy;
        cout << "Введите координаты треугольника " << i + 1 << " (ax ay bx by cx cy): ";
        cin >> ax >> ay >> bx >> by >> cx >> cy;
        triangles.emplace_back(ax, ay, bx, by, cx, cy);
    }

    for (int i = 0; i < M; ++i) {
        double ax, ay, bx, by, cx, cy;
        cout << "Введите координаты прямоугольного треугольника " << i + 1 << " (ax ay bx by cx cy): ";
        cin >> ax >> ay >> bx >> by >> cx >> cy;
        rightTriangles.emplace_back(ax, ay, bx, by, cx, cy);
    }

    for (const auto &triangle : triangles) {
        triangle.printInfo();
        cout << "\n";
    }

    for (const auto &rightTriangle : rightTriangles) {
        rightTriangle.printInfo();
        cout << "\n";
    }

    double minArea = numeric_limits<double>::max();
    double maxArea = numeric_limits<double>::min();
    int minIndex = -1, maxIndex = -1;

    for (int i = 0; i < triangles.size(); ++i) {
        double area = triangles[i].area();
        if (area < minArea) {
            minArea = area;
            minIndex = i;
        }
        if (area > maxArea) {
            maxArea = area;
            maxIndex = i;
        }
    }

    cout << "Треугольник с минимальной площадью (Индекс: " << minIndex << "):\n";
    triangles[minIndex].printInfo();
    cout << "\n";

    cout << "Треугольник с максимальной площадью (Индекс: " << maxIndex << "):\n";
    triangles[maxIndex].printInfo();
    cout << "\n";

    cout << "Прямоугольные треугольники с одинаковыми координатами:\n";
    for (int i = 0; i < rightTriangles.size(); ++i) {
        for (int j = i + 1; j < rightTriangles.size(); ++j) {
            if (rightTriangles[i].isRight() && rightTriangles[j].isRight() &&
                rightTriangles[i].area() == rightTriangles[j].area()) {
                cout << "  Прямоугольный треугольник " << i << " идентичен прямоугольному треугольнику " << j << "\n";
            }
        }
    }

    return 0;
}

/*
пример входных данных

Введите количество треугольников: 3
Введите количество прямоугольных треугольников: 2
Введите координаты треугольника 1 (ax ay bx by cx cy): 0 0 3 0 0 4
Введите координаты треугольника 2 (ax ay bx by cx cy): 1 1 4 5 7 8
Введите координаты треугольника 3 (ax ay bx by cx cy): 0 0 5 0 0 5
Введите координаты прямоугольного треугольника 1 (ax ay bx by cx cy): 0 0 3 0 0 4
Введите координаты прямоугольного треугольника 2 (ax ay bx by cx cy): 0 0 5 0 0 12
*/