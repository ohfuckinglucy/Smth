#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include "bstree.h"
#include <iomanip>

using namespace std;

int main() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    Node* tree = nullptr;

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();


    sort(words.begin(), words.end());

    for (int i = 1; i <= 200000; ++i) {
        tree->add(tree, words[i - 1], i - 1);

        if (i % 10000 == 0) {
            string w = words[getRand(0, i - 1)];
            double t = wtime();
            Node* node = tree->LookUp(tree, w);
            t = wtime() - t;

            cout << i << "\t"<< fixed << setprecision(9) << t << endl;
        }
    }

    return 0;
}
