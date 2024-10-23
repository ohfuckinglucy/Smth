#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include "bstree.h"
#include "iomanip"
#include "RandTime.h"

using namespace std;

int main() {
    ifstream file("res.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    Node* tree = nullptr;

    for (int i = 1; i <= 200000; ++i) {
        if(tree == nullptr) {
            tree = new Node(words[i - 1], i - 1);
        } else {
            tree->add(tree, words[i - 1], i - 1);
        }

        if (i % 10000 == 0) {
            string w = words[getRand(0, i - 1)];

            // Измерение времени выполнения функции add
            double tAdd = wtime();
            tree->add(tree, w, i);
            tAdd = wtime() - tAdd;

            cout << setw(7) << left << i << setw(10) << left << fixed << setprecision(7) << left << tAdd << endl;
        }
    }

    return 0;
}
