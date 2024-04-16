#include <iostream>
#include <cmath>

using namespace std;

// Функция для вычисления биномиального коэффициента
int binomialCoefficient(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
}

int main() {
    int x = 2;
    int y = 3;
    int z = 5;
    int n = 6; // степень разложения

    // Вычисление коэффициента a
    int a_coefficient = binomialCoefficient(n, 1) * pow(x, 2 * (n - 1)) * pow(y, 1);
    cout << "Коэффициент a = " << a_coefficient << "x^" << 2 * (n - 1) << " * y^1 * z^0" << endl;

    // Вычисление коэффициента b
    int b_coefficient = binomialCoefficient(n, 3) * pow(x, 2 * (n - 3)) * pow(y, 3);
    cout << "Коэффициент b = " << b_coefficient << "x^" << 2 * (n - 3) << " * y^3 * z^0" << endl;

    // Вычисление коэффициента c
    int c_coefficient = binomialCoefficient(n, 5) * pow(x, 2 * (n - 5)) * pow(z, 5);

    // Исправлено:
    a_coefficient = pow(a_coefficient, n);
    b_coefficient = pow(b_coefficient, n);
    c_coefficient = pow(c_coefficient, n);

    cout << "Коэффициент c = " << c_coefficient << "x^" << 2 * (n - 5) << " * y^0 * z^" << n << endl;

    return 0;
}