#include <iostream>
#include <stack>

using namespace std;

// Функция для вывода стека
void printStack(stack<int> s) {
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

int main() {
    stack<int> originalStack, evenStack;
    int n;

    // Ввод количества элементов
    cout << "Введите количество элементов: ";
    cin >> n;

    // Ввод элементов и формирование оригинального стека
    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        originalStack.push(num);
    }

    // Переписывание четных элементов в новый стек
    stack<int> tempStack = originalStack; // Копия оригинального стека для итерации
    while (!tempStack.empty()) {
        int num = tempStack.top();
        tempStack.pop();
        if (num % 2 == 0) {
            evenStack.push(num);
        }
    }

    // Вывод оригинального стека
    cout << "Оригинальный стек: ";
    printStack(originalStack);

    // Вывод стека с четными элементами
    cout << "Стек с четными элементами: ";
    printStack(evenStack);

    return 0;
}
