#include <iostream>
#include <queue>

int INT_MIN = 0;

using namespace std;

int main() {
    queue<int> q;
    int num, prev = INT_MIN;
    cout << "Enter integer numbers (enter -1 to stop):\n";
    while (true) {
        cin >> num;
        if (num == -1)
            break;
        q.push(num);
    }
    queue<int> k = q;
    queue<int> increasingQueue;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        if (current > prev) {
            increasingQueue.push(current);
            prev = current;
        }
    }

    cout << "Изначальная очередь: ";
    while (!k.empty()) {
        cout << k.front() << " ";
        k.pop();
    }
    cout << endl;
    cout << "Возрастающая очередь: ";
    while (!increasingQueue.empty()) {
        cout << increasingQueue.front() << " ";
        increasingQueue.pop();
    }
    cout << endl;

    return 0;
}
