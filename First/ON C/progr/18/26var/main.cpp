#include <iostream>
#include <vector>

using namespace std;

void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    vector<float> Y;
    vector<float> T;
    
    // Чтение данных из файла Y.txt
    FILE *f_y;
    f_y = fopen("Y.txt", "r");
    if (f_y == NULL) {
        cerr << "Ошибка открытия файла Y.txt" << endl;
        return 1;
    }

    float value;
    while (fscanf(f_y, "%f", &value) == 1) {
        Y.push_back(value);
    }
    fclose(f_y);
    cout << "Прочитано " << Y.size() << " значений из файла Y.txt" << endl;

    // Чтение данных из файла T.txt
    FILE *f_t;
    f_t = fopen("T.txt", "r");
    if (f_t == NULL) {
        cerr << "Ошибка открытия файла T.txt" << endl;
        return 1;
    }
    while (fscanf(f_t, "%f", &value) == 1) {
        T.push_back(value);
    }
    fclose(f_t);
    cout << "Прочитано " << T.size() << " значений из файла T.txt" << endl;
    if (!Y.empty() && !T.empty()) {
        cout << "Заполнение массива прошло успешно!"<< endl;
    }else{
        cout << "По крайней мере один из массивов пуст." << endl;
        return 1;
    }

    for (auto itT = T.begin(); itT != T.end(); ++itT) {
        cout << "T = " << *itT << " Y = ";
    
        size_t index = distance(T.begin(), itT) % Y.size();
        
        cout << Y[index] << endl;
    }

    vector<float> C;
    for (float y : Y) {
        if (y > 3) {
            C.push_back(y);
        }
    }

    if (!C.empty()) {
        cout << "Сортировка массива C..." << endl;
        BubbleSort(C);
        cout << "Отсортированные значения из вектора C (больше 3):" << endl;
    for (float c : C) {
        cout << c << endl;
}
    }else{
        cout << "Вектор C пуст, сортировка не требуется" << endl;
    }
}