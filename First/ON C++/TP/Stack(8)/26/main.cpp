#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> stack1, stack2;
    cout << "Enter 8 numbers for stack 1:\n";
    for (int i = 0; i < 8; ++i) {
        int num;
        cin >> num;
        stack1.push(num);
    }
    cout << "Enter 8 numbers for stack 2:\n";
    for (int i = 0; i < 8; ++i) {
        int num;
        cin >> num;
        stack2.push(num);
    }

    stack<int> tempStack1 = stack1;
    stack<int> tempStack2 = stack2;

    stack<int> stack3;
    
    for (int i = 0; i < 8; ++i) {
        int num1 = tempStack1.top();
        tempStack1.pop();
        int num2 = tempStack2.top();
        tempStack2.pop();
        stack3.push(num1 + num2);
    }

    cout << "Stack 1: " << endl;
    while (!stack1.empty()) {
        cout << stack1.top() << " ";
        stack1.pop();
    }
    cout << endl;

    cout << "Stack 2: " << endl;
    while (!stack2.empty()) {
        cout << stack2.top() << " ";
        stack2.pop();
    }
    cout << endl;

    cout << "Stack 3(Сумма 1 и 2): " << endl;
    while (!stack3.empty()) {
        cout << stack3.top() << " ";
        stack3.pop();
    }
    cout << endl;

    return 0;
}
