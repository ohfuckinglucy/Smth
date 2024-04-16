#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Функция для вывода подмножества
void printSubset(int i, const vector<int>& elements, const vector<bool>& subset) {
    cout << i << " - ";
    for (size_t j = 0; j < subset.size(); ++j) {
        cout << subset[j];
    }
    cout << " - {";
    bool first = true;
    for (int j = 0; j < elements.size(); ++j) {
        if (subset[j]) {
            if (!first) {
                cout << ", ";
            }
            cout << elements[j];
            first = false;
        }
    }
    cout << "}" << endl;
}

// Функция для генерации и вывода всех подмножеств
void generateSubsets(const vector<int>& elements) {
    int n = elements.size();
    vector<bool> subset(n, false);

    // Вывод пустого множества
    cout << "0 - ";
    for (int j = 0; j < n; ++j) {
        cout << "0";
    }
    cout << " - {}\n";

    // Генерация подмножеств
    subset[0] = true;
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                subset[j] = true;
            } else {
                subset[j] = false;
            }
        }
        printSubset(i, elements, subset);
    }
}

int main() {
    int n;
    cout << "Введите количество элементов в множестве: ";
    cin >> n;
    
    if (n <= 0){
        cout << "Что за бред?!" << endl;
        exit(1);
    }

    vector<int> elements(n);
    cout << "Введите элементы множества:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> elements[i];
    }

    sort(elements.begin(), elements.end());
    elements.erase(unique(elements.begin(), elements.end()), elements.end());

    generateSubsets(elements);

    return 0;
}
